# include "material.h"
Material :: Material ()
{
    ambient = QVector4D (1 , 1, 1, 1.0) ;
    diffuse = QVector4D (0.0 , 0.7 , 0.1 , 1.0) ;
    specular = QVector4D (1 , 1 ,1 , 1.0) ;
    shininess = 200.0;
}
