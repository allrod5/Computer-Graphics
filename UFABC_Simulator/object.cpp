#include "object.h"

Object::Object()
{
	vertices = NULL;
	colors = NULL;
	indices = NULL;

	vboVertices = NULL;
	vboColors = NULL;
	vboIndices = NULL;

	shaderProgram = NULL;
	vertexShader = NULL;
	fragmentShader = NULL;
	colorTexture = NULL;

	currentShader = 0;
	image = QImage(":/textures/jellyfish.jpg");
}

Object::~Object()
{
	destroyVBOs();
	destroyShaders();
}

void Object::loadObject(QString fileName)
{
	std::ifstream stream ;
	stream.open(fileName.toUtf8(), std::ifstream::in);
	if(! stream.is_open()) {
		qWarning("Cannot open file.");
		return ;
	}
	std::string line ;
	stream >> line ;
	stream >> numVertices >> numFaces >> line ;

	delete [] vertices ;
	vertices = new QVector4D[numVertices];
	delete [] indices ;
	indices = new unsigned int[numFaces * 3];

	if(numVertices > 0) {
		double minLim = std::numeric_limits < double >::min();
		double maxLim = std::numeric_limits < double >::max();
		QVector4D max(minLim, minLim, minLim, 1.0);
		QVector4D min(maxLim, maxLim, maxLim, 1.0);

		for(unsigned int i = 0; i < numVertices ; i ++) {
			double x, y, z;
			stream >> x >> y >> z;
			max.setX(qMax < double >(max .x(), x));
			max.setY(qMax < double >(max .y(), y));
			max.setZ(qMax < double >(max .z(), z));
			min.setX(qMin < double >(min .x(), x));
			min.setY(qMin < double >(min .y(), y));
			min.setZ(qMin < double >(min .z(), z));

			vertices[i] = QVector4D(x, y, z, 1.0);
		}
		midPoint = ((min + max)* 0.5).toVector3D();
		invDiag = 1 /(max - min).length();
	}
	for(unsigned int i = 0; i < numFaces ; i ++) {
		unsigned int a, b, c;
		stream >> line >> a >> b >> c;
		indices[i * 3] = a;
		indices[i * 3 + 1] = b;
		indices[i * 3 + 2] = c;
	}

	//emit statusBarMessage(QString("Samples %1, Faces %2,Zoom %3").arg(numVertices).arg(numFaces).arg(zoom));

	stream.close();
	calculateNormals();
	genTexCoordsCylinder();
	createVBOs();
	createShaders();
}

void Object::calculateNormals()
{
	QVector3D a, b, c, tmp;
	normals = new QVector3D[numVertices];
	for(unsigned int i = 0; i < numFaces ; i ++) {
		a = QVector3D(vertices[indices[i * 3]]);
		b = QVector3D(vertices[indices[i * 3 + 1]]);
		c = QVector3D(vertices[indices[i * 3 + 2]]);
		tmp = QVector3D::crossProduct((b-a),(c-a)).normalized();
		normals[indices[i * 3]] += tmp;
		normals[indices[i * 3 + 1]] += tmp;
		normals[indices[i * 3 + 2]] += tmp;
	}
	for(unsigned int i=0; i<numVertices; i++) {
		normals[i].normalize();
	}
}

void Object::genTexCoordsCylinder()
{
	if(texCoords)
		delete [] texCoords ;
	// Compute minimum and maximum values
	float fmax = std::numeric_limits<float>::max();
	float minz = fmax ;
	float maxz = - fmax ;
	for(int i =0; i < numVertices ; ++ i) {
		if(vertices[i]. z()< minz)minz = vertices[i]. z();
		if(vertices[i]. z()> maxz)maxz = vertices[i]. z();
	}
	texCoords = new QVector2D[numVertices];
	for(int i =0; i < numVertices ; ++ i) { // https :// en . wikipedia . org / wiki / Atan2
		float s =(atan2(vertices[i].y(), vertices[i].x())+M_PI)/(2*M_PI);
		float t = 1.0f -(vertices[i].z()- minz)/(maxz - minz);
		texCoords[i] = QVector2D(s,t);
	}
}

void Object::drawObject(Camera camera, Light light, float zoom, float camX, float camY, float camZ, QQuaternion rotation)
{
	if(!vboVertices)
		return;

	modelView.setToIdentity();
	modelView.lookAt(camera.eye, camera .at, camera.up);
	modelView.translate(0, 0, zoom);
	modelView.translate(camX, camY, camZ);
	modelView.rotate(rotation);
	modelView.scale(invDiag, invDiag, invDiag);
	modelView.translate(- midPoint);
	shaderProgram->bind();
	QVector4D ambientProduct = light.ambient * material.ambient;
	QVector4D diffuseProduct = light.diffuse * material.diffuse;
	QVector4D specularProduct = light.specular * material.specular;

	vbocoordText->bind();
	shaderProgram->enableAttributeArray("vcoordText");
	shaderProgram->setAttributeBuffer("vcoordText", GL_FLOAT, 0, 2, 0);
	//texture->bind(0);
	//shaderProgram->setUniformValue("colorTexture", 0);


	if(colorTexture!=NULL) {
		delete colorTexture;
		colorTexture = NULL;
	}
	colorTexture = new QOpenGLTexture(image);
	colorTexture->bind(0);
	shaderProgram->setUniformValue("colorTexture", 0);
	/*colorTextureLayer->bind(1);
	shaderProgram->setUniformValue("colorTextureLayer", 1);*/

	shaderProgram->setUniformValue("lightPosition", light.position);
	shaderProgram->setUniformValue("ambientProduct",ambientProduct);
	shaderProgram->setUniformValue("diffuseProduct",diffuseProduct);
	shaderProgram->setUniformValue("specularProduct",specularProduct);
	shaderProgram->setUniformValue("shininess", static_cast<GLfloat>(material.shininess));
	shaderProgram->setUniformValue("lightIntensity", light.intensity);
	shaderProgram->setUniformValue("lightAmbient", light.ambient);
	shaderProgram->setUniformValue("lightDiffuse", light.diffuse);
	shaderProgram->setUniformValue("modelView", modelView);
	shaderProgram->setUniformValue("normalMatrix", modelView.normalMatrix());
	shaderProgram->setUniformValue("projectionMatrix",projectionMatrix);

	vboVertices->bind();
	shaderProgram->enableAttributeArray("vPosition");
	shaderProgram->setAttributeBuffer("vPosition", GL_FLOAT, 0, 4, 0);
	vboColors->bind();
	shaderProgram->enableAttributeArray("vNormal");
	shaderProgram->setAttributeBuffer("vNormal", GL_FLOAT, 0, 3, 0);
	vboIndices->bind();
	glDrawElements(GL_TRIANGLES, numFaces * 3, GL_UNSIGNED_INT, 0);
	vboIndices->release();
	vboVertices->release();
	colorTexture->release(0);
	vbocoordText->release();
	shaderProgram->release();
	//delete colorTexture;
	/*colorTextureLayer->release(1);*/
}

void Object::createVBOs() {
	destroyVBOs();
	vboVertices = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	vboVertices->create();
	vboVertices->bind();
	vboVertices->setUsagePattern(QOpenGLBuffer::StaticDraw);
	vboVertices->allocate(vertices, numVertices * sizeof(QVector4D));
	delete [] vertices ;
	vertices = NULL ;
	vboIndices = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
	vboIndices->create();
	vboIndices->bind();
	vboIndices->setUsagePattern(QOpenGLBuffer::StaticDraw);
	vboIndices->allocate(indices, numFaces * 3 * sizeof(unsigned int));
	vboColors = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	vboColors->create();
	vboColors->bind();
	vboColors->setUsagePattern(QOpenGLBuffer::StaticDraw);
	vboColors->allocate(normals, numVertices * sizeof(QVector3D));

	vbocoordText = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	vbocoordText->create();
	vbocoordText->bind();
	vbocoordText->setUsagePattern(QOpenGLBuffer::StaticDraw);
	vbocoordText->allocate(texCoords, numVertices * sizeof(QVector2D));

	delete [] normals ;
	colors = NULL ;
	delete [] indices ;
	indices = NULL ;
}

void Object::destroyVBOs()
{
	if(vboVertices) {
		vboVertices->release(); // bind opposite
		// cannot be necessary as the QOpenGLBuffer destroys the
		//data on OpenGL server
		vboVertices->destroy(); // create opposite
		delete vboVertices ;
		vboVertices = NULL ;
	}
		if(vboIndices) {
		vboIndices->release();
		vboIndices->destroy();
		delete vboIndices ;
		vboIndices = NULL ;
	}
	if(vboColors) {
		vboColors->release();
		delete vboColors ;
		vboColors = NULL ;
	}
}

void Object::destroyShaders()
{
	delete vertexShader ;
	vertexShader = NULL ;
	delete fragmentShader ;
	fragmentShader = NULL ;

	if(shaderProgram) {
		shaderProgram->release();
		delete shaderProgram ;
		shaderProgram = NULL ;
	}
}

void Object::createShaders()
{
	destroyShaders();
	// flat shading https :// www.packtpub.com / books / content / basics - glsl -40 - shaders
	QString vertexShaderFile[] = {
	   ":/shaders/flat_vshader.glsl",
	   ":/shaders/gouraud_vshader.glsl",
	   ":/shaders/phong_vshader.glsl",
	   ":/shaders/cartoon_vshader.glsl",
	   ":/shaders/texture_vshader.glsl",
	   ":/shaders/normal_vshader.glsl",
	   ":/shaders/blinn-phong_vshader.glsl"
	};
	QString fragmentShaderFile[] = {
		":/shaders/flat_fshader.glsl",
		":/shaders/gouraud_fshader.glsl",
		":/shaders/phong_fshader.glsl",
		":/shaders/cartoon_fshader.glsl",
		":/shaders/texture_fshader.glsl",
		":/shaders/normal_fshader.glsl",
		":/shaders/blinn-phong_fshader.glsl"
	};
	vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
	if(! vertexShader->compileSourceFile(vertexShaderFile[currentShader]))
	qWarning()<< vertexShader->log();
	fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
	if(! fragmentShader->compileSourceFile(fragmentShaderFile[currentShader]))
	qWarning()<< fragmentShader->log();
	shaderProgram = new QOpenGLShaderProgram ;
	shaderProgram->addShader(vertexShader);
	shaderProgram->addShader(fragmentShader);
	if(! shaderProgram->link())
	qWarning()<< shaderProgram->log()<< endl ;
}
