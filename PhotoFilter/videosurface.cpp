#include "videosurface.h"

VideoSurface::VideoSurface( QObject *parent) : QAbstractVideoSurface(parent)
{
 qDebug()<<"ola";
 rgbs=NULL;
 yuvs=NULL;
}

bool VideoSurface::present(const QVideoFrame& frame){
    if(frame.isValid()){
        QVideoFrame videoFrame(frame);
        QImage *img=NULL;
        if(videoFrame.map(QAbstractVideoBuffer::ReadOnly)){
            const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
            if(imageFormat == QImage::Format_Invalid){
                if(frame.pixelFormat()==QVideoFrame::Format_YUV420P){
                    if(rgbs!=NULL) delete rgbs;
                    yuvs= videoFrame.bits();
                    rgbs=  new uchar[videoFrame.bytesPerLine()*videoFrame.height()*3];
                    int width= videoFrame.width();
                    int height= videoFrame.height();
                    int outPtr=0;
                    int size = width * height;
                    for(int i=0;i<height;i++){
                        for(int j=0;j<width;j++){
                            //read the luminance and chromiance values
                            int Y = ((char)yuvs[i * width + j] & 0xff) ;

                            int Cr = ((char)yuvs[((i/2)*(width/2))+(j/2)+size] & 0xff) - 128;
                            int Cb = ((char)yuvs[((i/2)*(width/2))+(j/2)+size+(size/4)] & 0xff) - 128;
                            int R, G, B;
                            int C=Y-16;
                            int D=Cr;
                            int E=Cb;

                            //generate first RGB components
                            //B = Y1 + ((454 * Cb) >> 8);
                            B=((298*C)+(516*D)+128)>>8;
                            if(B < 0) B = 0; else if(B > 255) B = 255;
                            //G = Y1 - ((88 * Cb + 183 * Cr) >> 8);
                            G= ((298*C)-(100*D)-(208*E)+128)>>8;
                            if(G < 0) G = 0; else if(G > 255) G = 255;
                            //R = Y1 + ((359 * Cr) >> 8);
                            R=((C*298)+(E*409)+128) >>8;
                            if(R < 0) R = 0; else if(R > 255) R = 255;
                            //NOTE: this assume little-endian encoding
                            rgbs[outPtr++]  = (uchar)R;
                            rgbs[outPtr++]  = (uchar)G;
                            rgbs[outPtr++]=(uchar)B;
                        }
                    }
                    img= new QImage(rgbs,width,height, QImage::Format_RGB888);
                    //delete rgbs;
                    //delete yuvs;
                }
            }
            else{
                img=new QImage (frame.bits(),frame.width(),frame.height(),frame.bytesPerLine(),imageFormat);
            }


        }
        if(img!=NULL)
            emit signalSendImage(img);
        videoFrame.unmap();
    }

    return true;
}
bool VideoSurface::isFormatSupported(
         const QVideoSurfaceFormat &format, QVideoSurfaceFormat *similar) const
 {
     Q_UNUSED(similar);

     QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
     QSize size = format.frameSize();

     return imageFormat != QImage::Format_Invalid
             && !size.isEmpty()
             && format.handleType() == QAbstractVideoBuffer::NoHandle;
 }
QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const{
    return QList<QVideoFrame::PixelFormat>()
            << QVideoFrame::Format_RGB32
            << QVideoFrame::Format_ARGB32;
}
