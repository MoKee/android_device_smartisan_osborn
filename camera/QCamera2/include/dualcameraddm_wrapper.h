#ifndef __DUALCAMERADDM_WRAPPER_H__
#define __DUALCAMERADDM_WRAPPER_H__

void cpcommon_jtQq0GW21f();
void cpcommon_xqO2U0T3wU(unsigned char const*, unsigned char const*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned char*, unsigned char*, unsigned int, unsigned int, unsigned int, unsigned int);
void cpcommon_OXEGJHWLJa(unsigned char const*, unsigned char const*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned char*, unsigned int);
void cpcommon_3QHx3Ewwnl(unsigned char const*, unsigned int, unsigned int, unsigned int, unsigned char*, unsigned char*, unsigned int, unsigned int);

void dualcameraddm_qSv3fcF7Tp(int, int, int&, int&);
void dualcameraddm_k5DFT9dbFc(unsigned char const*, unsigned char const*, int, int, int, int, unsigned char const*, unsigned char const*, int, int, int, int, unsigned char*, int, int, int, int&, int&, int&, int&, char const*, char const*, char const*, float, bool, int, int&, char const*&);
void dualcameraddm_sKy6qu3UbY(unsigned char const*, int, int, int, unsigned char*, int, int, int);

class DualCameraEffects {
public:
    class EffectType {
    };
};

namespace qrcp {
    class DualCameraDDMEffects {
    public:
        void _n27g24FFFp(DualCameraEffects*&, unsigned char const*, int, int, int, unsigned char const*, int, int, int, int, int, int, int, int, int, float);
        void _kW7tcPL7jz(DualCameraEffects*&, unsigned char const*, unsigned char const*, int, int, int, int, unsigned char const*, int, int, int, int, int, int, int, int, int, float);
        void _nmMkwDL9CQ(DualCameraEffects*&);
        void _cZ38NjVp6X(DualCameraEffects*, int, int, int, float, unsigned char*, int, int, int, int&, char const*&);
        void _kpvUScvK8u(DualCameraEffects*, int, int, int, float, unsigned char*, unsigned char*, int, int, int, int, int&, char const*&);
        void _ySf5prRkfD(int, char const*&, char const*&);
    };
};

class DualCameraDDM {
public:
    class DualCameraImpl {
    public:
        DualCameraImpl(cv::Mat const&, cv::Mat const&, std::string const&, bool, float, bool);

        void renderEffect(DualCameraEffects::EffectType, cv::Point_<int> const&, bool, cv::Mat&, cv::Rect_<int>&, cv::Size_<int> const&, float);
    };

    void _qcpyQa27fH(DualCameraDDM::DualCameraImpl*, unsigned char*, int);
    void _hVfwQTZ2pp(DualCameraDDM::DualCameraImpl*, unsigned int&, unsigned int&);
    void _s9Es4pTxpz(int, char const*&, char const*&);
    void _68BH2ykeQC(DualCameraDDM::DualCameraImpl*, unsigned char const*, int, int, int, int, int, unsigned char*, int, int, int, int&, int&, int&, int&, bool);
    void _4d43vxLSmN(DualCameraDDM::DualCameraImpl*&);
    void _tTaBQTfszm(DualCameraDDM::DualCameraImpl*, unsigned char*, int, unsigned char*, int, int, int);
    void _c7dsYP2AmR(DualCameraDDM::DualCameraImpl*, int, int, int, int, float, unsigned char*, int, int, int, int&, int&, int&, int&, bool);
    void _eJbE28PNR8(DualCameraDDM::DualCameraImpl*&, unsigned char const*, int, int, int, unsigned char const*, int, int, int, char const*, bool, float, bool);
};

class LiveSceneAppApi {
public:
    LiveSceneAppApi();
    virtual ~LiveSceneAppApi();

    void _cHyVhWWX9u();
    void _u1aFCJPDWx(unsigned char*, unsigned int, unsigned int, unsigned int, unsigned int);
    void _ok7IAq2gRi();
    void _oLZC0D8jBS(unsigned char const*, unsigned int, unsigned int, unsigned int, unsigned char const*, unsigned int, unsigned int, unsigned int, char const*, unsigned int, unsigned int);
};

#endif /* __DUALCAMERADDM_WRAPPER_H__ */
