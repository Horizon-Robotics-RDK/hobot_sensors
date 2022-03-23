/***************************************************************************
 * COPYRIGHT NOTICE
 * Copyright 2020 Horizon Robotics, Inc.
 * All rights reserved.
 ***************************************************************************/
#ifndef MIPI_CAP_H
#define MIPI_CAP_H
#include "video_comm.h"
#include "x3_sdk_wrap.h"
#include "camera_struct_define.h"
#include "x3_utils.h"
#include <vector>

typedef struct {
	int 				m_enable;
	int 				m_vin_enable; // 使能标志
	x3_vin_info_t		m_vin_info; // 包括 sensor、 mipi、isp、 ldc、dis的配置
	int 				m_vps_enable;
	x3_vps_infos_t		m_vps_infos; // vps的配置，支持多个vps group
	int 				m_venc_enable;
	x3_venc_info_t		m_venc_info; // H264、H265、Jpeg、MJpeg编码通道配置
	int 				m_vdec_enable;
	x3_vdec_info_t		m_vdec_info; // H264、H265解码通道配置
} x3_modules_info_t;

typedef struct {
    x3_modules_info_t 	m_infos; // X3 各媒体模块配置
	pthread_t m_rgn_thread;//tsThread		m_rgn_thread;
	pthread_t		m_vot_thread;//tsThread		m_vot_thread;

	int			m_dst_width; // 输出给usb host的图像宽度
	int			m_dst_height; // 输出给usb host的图像高度
	int			m_dst_stride; // 输出给usb host的图像的字节宽度

	int			m_payload_type; // 输出给usb host的数据格式，NV12、h264、mjpeg
	int			m_venc_chn; // 如果是h264、mjpeg编码数据，使用到的编码通道
	int			m_venc_width; // 编码器有宽高输出的字节对齐需求，H264 8字节对齐，mjpeg
	int			m_venc_height;

	int			m_ptz_test_enable; // 测试 vps crop 左上角一个小图，再放大到usb host要求的目标图像
} x3_usb_cam_t;

class MipiDevice :public CVideoComm
{
public:
    MipiDevice();
    int OpenCamera(const TCamInfo* pCamInfo);
    int GetFrame(void **, unsigned int*);
    // 如果有 vps ，就 输出vps 的分层数据
    int GetVpsFrame(int nChnID, int *nVOutW, int *nVOutH, void **, unsigned int*);
private:
	int mf37_linear_vin_param_init(x3_vin_info_t* vin_info);
	int mf37_dol2_vin_param_init(x3_vin_info_t* vin_info);
    int mimx415_linear_vin_param_init(x3_vin_info_t* vin_info);
    int x3_cam_uninit(void);
    int x3_usb_cam_stop(void);
    int x3_usb_cam_start(void);
    int init_param(void);
    // 得到可用的 pipe_id,0-7,进程id 对应 pipe_id,假设pipe_id对应的进程已不存在，则使用id，并更新为当前进程id
    int get_available_pipeid();
private:
	virtual int doCapStreamLoop();
	virtual int childStart();
	virtual int childStop();
public:
private:
    struct buffer
    {
        void * start;
        size_t length;
    };
    x3_usb_cam_t m_oX3UsbCam;
	hard_capability_t m_oHardCapability;
    //char *m_pDevName;
    int m_fdVideoDev;
	int buffer_size;
    buffer* buffers;
	
  	std::vector<pym_buffer_t> buffers_;

    unsigned int n_buffers;
    int m_curCaptureIdx;		//正在读取的帧序号	
private:
   
};

#endif // VIDEO_CAP_H

