# ifndef LIGHT_H
# define LIGHT_H
# include <QVector4D>
# include <QVector3D>
class Light
{
public :
    Light () ;
    QVector4D position ;
    QVector4D ambient ;
    QVector4D diffuse ;
    QVector4D specular ;
    QVector3D intensity ;
};
# endif // LIGHT_H
