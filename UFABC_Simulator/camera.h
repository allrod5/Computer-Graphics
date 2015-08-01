# ifndef CAMERA_H
# define CAMERA_H
# include <QVector3D>
# include <QKeyEvent>
# include <fstream>
# include <limits>
# include <iostream>
class Camera
{
public :
    Camera ();
    QVector3D eye;
    QVector3D at;
    QVector3D up;
};
# endif // CAMERA_H
