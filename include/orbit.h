class Orbit
{
public:
    Orbit();
    GLfloat Rp;
    GLfloat Ra;
    GLfloat nu;
    GLfloat angle;
    void calc(GLfloat rx, GLfloat ry, GLfloat vx, GLfloat vy, GLfloat GM);
    void calc(GLfloat planet_x, GLfloat planet_y, GLfloat ship_x, GLfloat ship_y, GLfloat vx, GLfloat vy, GLfloat GM);
};