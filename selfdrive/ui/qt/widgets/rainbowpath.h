#ifndef RAINBOW_PATH_H
#define RAINBOW_PATH_H

#include <QObject>
#include <QLibrary>
#include <QLinearGradient>

class RainbowPath : public QObject {
    Q_OBJECT

public:
    explicit RainbowPath(QObject* parent = nullptr);
    ~RainbowPath();

    void updateState(double v_ego);
    void updateRotation();
    void updatePathGradient(QLinearGradient &bg);

private:
    // Qt wrapper for dynamic library loading
    QLibrary m_library;

    // Function pointers for the SO API
    typedef void* (*CreateFunc)();
    typedef void (*DestroyFunc)(void*);
    typedef void (*UpdateStateFunc)(void*, double);
    typedef void (*UpdateRotationFunc)(void*);
    typedef int (*GetColorsFunc)(void*, double*, int*, int);

    CreateFunc m_create;
    DestroyFunc m_destroy;
    UpdateStateFunc m_updateState;
    UpdateRotationFunc m_updateRotation;
    GetColorsFunc m_getColors;

    // Instance handle
    void* m_coreInstance;

    // Helper function
    bool loadLibraryFunctions();
};

#endif // RAINBOW_PATH_H
