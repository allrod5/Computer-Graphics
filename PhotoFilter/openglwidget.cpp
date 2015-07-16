#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{


    vboIndices=NULL;
    vboTextureCoordinate=NULL;
    vertexShader=NULL;
    fragmentShader=NULL;
    shaderProgram=NULL;
    imgOrig=NULL;
	currentShader = 0;
	dividerValue = 0.5;
}

OpenGLWidget::~OpenGLWidget(){
    destroyVBOs();
    destroyShaders();
    if(imgOrig) delete imgOrig;
}

void OpenGLWidget :: shaderChanged(int i)
{
	currentShader = i;
	createShaders() ;
	update();
}

void OpenGLWidget::destroyShaders(){
    if(vertexShader)delete vertexShader;
    vertexShader=NULL;
    if(fragmentShader)delete fragmentShader;
    fragmentShader=NULL;
    if(shaderProgram){
        shaderProgram->release();
         delete shaderProgram;
         shaderProgram=NULL;
    }
}
void OpenGLWidget::destroyVBOs(){
    if(vboTextureCoordinate){
        vboTextureCoordinate->release();
        delete vboTextureCoordinate;
        vboTextureCoordinate=NULL;
    }

    if(vboIndices){
        vboIndices->release();
        delete vboIndices;
        vboIndices=NULL;
    }
}

void OpenGLWidget::createShaders(){

	destroyShaders();

	QString vertexShaderFile [] = {
	   ":/original.vert",
	   ":/edgedetection.vert",
	   ":/gaussianblur.vert",
	   ":/bloom.vert",
	   ":/gammacorrection.vert",
	   ":/toon.vert",
	   ":/fisheye.vert",
	   ":/billboard.vert"
	};
	QString fragmentShaderFile [] = {
		":/original.frag",
		":/edgedetection.frag",
		":/gaussianblur.frag",
		":/bloom.frag",
		":/gammacorrection.frag",
		":/toon.frag",
		":/fisheye.frag",
		":/billboard.frag"
	};

	shaderProgram = new QOpenGLShaderProgram;
	shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex,FileOperationsFromResource::readFile(vertexShaderFile[currentShader]));
	shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment,FileOperationsFromResource::readFile(fragmentShaderFile[currentShader]));
	if(!shaderProgram->link()){
		qWarning() << shaderProgram->log() << endl;
	}

}


void OpenGLWidget::createVBOs(){
    destroyVBOs();//destroy previous (GPU allocated) VBOs
    //define coordinate texture=========================================
    QVector2D *qVector2DTextureCoordinate=new QVector2D[4];
    qVector2DTextureCoordinate[3]= QVector2D(0,0);
    qVector2DTextureCoordinate[2]=QVector2D(1,0);
    qVector2DTextureCoordinate[1]=QVector2D(1,1);
    qVector2DTextureCoordinate[0]=QVector2D(0,1);
    //end===============================================================

    //transfer coordenate  texture to gpu===============================
    vboTextureCoordinate = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboTextureCoordinate->create();
    vboTextureCoordinate->bind();
    vboTextureCoordinate->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboTextureCoordinate->allocate(qVector2DTextureCoordinate , 4*sizeof(QVector2D));
    //end===============================================================

    //define face to form one square====================================
    unsigned int  *indices = new unsigned int[2*3];
    indices[0]=0; indices[1]=1; indices[2]=2;
    indices[3]=2; indices[4]=3; indices[5]=0;
    //end===============================================================
    //transfer face to gpu==============================================
    vboIndices =new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    vboIndices ->create();
    vboIndices ->bind();
    vboIndices ->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboIndices ->allocate(indices , 2 * 3 *sizeof(unsigned int));
    //end===============================================================
    delete [] indices;
    delete qVector2DTextureCoordinate;
}

void OpenGLWidget::initializeGL(){
    this->createVBOs();
	this->createShaders();
    initializeOpenGLFunctions();

}

void OpenGLWidget::resizeGL(int w, int h){


}

void OpenGLWidget::slotSendImage(){
    makeCurrent();
    QOpenGLFramebufferObject fbo(240, 780);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glViewport(0, 0, 240,780);
    glMatrixMode(GL_PROJECTION);
    fbo.bind();

    paintImg(imgOrig);
    emit signalSendImage(new QImage(fbo.toImage()));

}
void OpenGLWidget::slotRecvImage(QImage *img){
    if(imgOrig) delete imgOrig;
    imgOrig=img;
    update();
}

void OpenGLWidget::sliderChanged(int i) {
	dividerValue = i/100.0;
	createShaders();
	update();
}

void OpenGLWidget::paintGL(){

    paintImg(imgOrig);
}

float OpenGLWidget::gauss(int x, float sigma2) {
	return exp( -(x*x) / (2*sigma2) )/(sqrt(2*sigma2*3.141593));
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	mouse = event->globalPos();
	createShaders();
	update();
}

void OpenGLWidget::paintImg(QImage *img){
    if(img==NULL) return;
    //create Vertices========================================
    QVector4D *vertices =new QVector4D[4];
    vertices[0]=  QVector4D(0,0,0,1);
    vertices[1]=  QVector4D((float)img->width(),0,0,1);
    vertices[2]=  QVector4D((float)img->width(),(float)img->height(),0,1);
    vertices[3]=  QVector4D(0,(float)img->height(),0,1);
    //end====================================================

    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram->bind();

    QOpenGLTexture * texture= new QOpenGLTexture(*img);
    //texture->setMagnificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::MirroredRepeat);
    texture->setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::MirroredRepeat);
    glActiveTexture(GL_TEXTURE0);
    texture->bind();
    glUniform1i(glGetUniformLocation(shaderProgram->programId(), "texture1"), 0);


	shaderProgram->setUniformValue("mouse", mouse);

	float lensSize = 0.2;
	shaderProgram->setUniformValue("lensSize",static_cast<GLfloat>(lensSize));

    QVector2D *resolution= new QVector2D(img->width(), img->height());
    shaderProgram->setUniformValue("u_resolution",*resolution);

	float EdgeThreshold = 0.1;
	shaderProgram->setUniformValue("EdgeThreshold",static_cast<GLfloat>(EdgeThreshold));

	float BillboardGrid = 0.15;
	shaderProgram->setUniformValue("grid",static_cast<GLfloat>(BillboardGrid));
	shaderProgram->setUniformValue("dividerValue",static_cast<GLfloat>(dividerValue));
	float BillboardX = 0.1;
	shaderProgram->setUniformValue("step_x",static_cast<GLfloat>(BillboardX));
	float BillboardY = 0.1;
	shaderProgram->setUniformValue("step_y",static_cast<GLfloat>(BillboardY));
	float BillboardOpacity = 0.3;
	shaderProgram->setUniformValue("qt_Opacity",static_cast<GLfloat>(BillboardOpacity));

	char uniName[20];
	float weights[5], sum, sigma2 = 4.0f;
	weights[0] = gauss(0,sigma2);
	sum = weights[0];
	for( int i = 1; i < 5; i++ ) {
		weights[i] = gauss(i, sigma2);
		sum += 2 * weights[i];
	}
	for( int i = 0; i < 5; i++ ) {
		snprintf(uniName, 20, "Weight[%d]", i);
		shaderProgram->setUniformValue(uniName, weights[i] / sum);
	}

	float BlurSize = 4.0;
	shaderProgram->setUniformValue("blurSize",static_cast<GLfloat>(BlurSize));

	float Gamma = 2.4;
	shaderProgram->setUniformValue("Gamma",static_cast<GLfloat>(Gamma));

	float magTol = 0.3;
	shaderProgram->setUniformValue("magTol",static_cast<GLfloat>(magTol));
	float quantize = 8.0;
	shaderProgram->setUniformValue("quantize",static_cast<GLfloat>(quantize));

    //tansfer vertices to gpu===========================================
    QOpenGLBuffer *vboVertices = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vboVertices ->create();
    vboVertices ->bind();
    vboVertices ->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboVertices ->allocate(vertices , 4 *sizeof(QVector4D));
    vboVertices->bind();//vertices is linked with a_position
    shaderProgram->enableAttributeArray("a_position");//vertices is linked with a_position
    shaderProgram->setAttributeBuffer("a_position",GL_FLOAT, 0,4,0);//vertices is linked with a_position
    //end===============================================================

    //coordenate  texture is linked with a_texCoord"====================
    vboTextureCoordinate->bind();
    shaderProgram->enableAttributeArray("a_texCoord");
    shaderProgram->setAttributeBuffer("a_texCoord",GL_FLOAT, 0,2,0);
    //end===============================================================

    vboIndices->bind();
    glDrawElements(GL_TRIANGLES,2*3,GL_UNSIGNED_INT,0);
    vboIndices->release();
    texture->release();

    vboVertices->release();
    shaderProgram->release();

    delete vboVertices;
    delete [] vertices;
    delete resolution;
    delete texture;

}
