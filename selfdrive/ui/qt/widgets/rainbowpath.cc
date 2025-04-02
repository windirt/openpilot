#include "selfdrive/ui/qt/widgets/rainbowpath.h"
#include <QDebug>

RainbowPath::RainbowPath(QObject* parent) :
    QObject(parent),
    m_create(nullptr),
    m_destroy(nullptr),
    m_updateState(nullptr),
    m_updateRotation(nullptr),
    m_getColors(nullptr),
    m_coreInstance(nullptr)
{
    #ifdef QCOM2
    QString libraryPath = "../../third_party/rainbow/aarch64/librainbow.so";
    #else
    QString libraryPath = "../../third_party/rainbow/x86_64/librainbow.so";
    #endif

    // Initialize the library with the full path
    m_library.setFileName(libraryPath);

    if (loadLibraryFunctions()) {
        // Create instance
        if (m_create) {
            m_coreInstance = m_create();
        }
    }
}


RainbowPath::~RainbowPath() {
    if (m_coreInstance && m_destroy) {
        m_destroy(m_coreInstance);
    }

    // QLibrary automatically unloads when instance is destroyed
}

bool RainbowPath::loadLibraryFunctions() {
    // Load the library
    if (!m_library.load()) {
        qWarning() << "Failed to load rainbow_path_core library:" << m_library.errorString();
        return false;
    }

    // Load all required functions
    m_create = reinterpret_cast<CreateFunc>(m_library.resolve("rainbow_path_core_create"));
    m_destroy = reinterpret_cast<DestroyFunc>(m_library.resolve("rainbow_path_core_destroy"));
    m_updateState = reinterpret_cast<UpdateStateFunc>(m_library.resolve("rainbow_path_core_update_state"));
    m_updateRotation = reinterpret_cast<UpdateRotationFunc>(m_library.resolve("rainbow_path_core_update_rotation"));
    m_getColors = reinterpret_cast<GetColorsFunc>(m_library.resolve("rainbow_path_core_get_colors"));

    // Check if all functions were resolved
    if (!m_create || !m_destroy || !m_updateState || !m_updateRotation ||
        !m_getColors) { //|| !m_setEnabled || !m_isEnabled) {
        qWarning() << "Failed to resolve functions from rainbow_path_core library:" << m_library.errorString();
        m_library.unload();
        return false;
    }

    return true;
}

void RainbowPath::updateState(double v_ego) {
    if (m_coreInstance && m_updateState) {
        m_updateState(m_coreInstance, v_ego);
    }
}

void RainbowPath::updateRotation() {
    if (m_coreInstance && m_updateRotation) {
        m_updateRotation(m_coreInstance);
    }
}

void RainbowPath::updatePathGradient(QLinearGradient &bg) {
    if (m_coreInstance && m_getColors) {
        constexpr int NUM_COLORS = 25;
        double positions[NUM_COLORS];
        int colors[NUM_COLORS];

        // Get colors from the core library
        int count = m_getColors(m_coreInstance, positions, colors, NUM_COLORS);

        // Clear and reset gradient colors
        bg.setStops(QGradientStops());
        bg.setSpread(QGradient::RepeatSpread);

        for (int i = 0; i < count; i++) {
            QColor color = QColor::fromRgba(colors[i]);
            bg.setColorAt(positions[i], color);
        }
    }
}
