#ifdef TARGET_OPENGLES

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

void
gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

void
gluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLfloat centerx,
          GLfloat centery, GLfloat centerz, GLfloat upx, GLfloat upy,
          GLfloat upz);

GLint
gluProject(GLfloat objx, GLfloat objy, GLfloat objz,
           const GLfloat modelMatrix[16],
           const GLfloat projMatrix[16],
           const GLint viewport[4],
           GLfloat *winx, GLfloat *winy, GLfloat *winz);

GLint
gluUnProject(GLfloat winx, GLfloat winy, GLfloat winz,
             const GLfloat modelMatrix[16],
             const GLfloat projMatrix[16],
             const GLint viewport[4],
             GLfloat *objx, GLfloat *objy, GLfloat *objz);


GLint
gluUnProject4(GLfloat winx, GLfloat winy, GLfloat winz, GLfloat clipw,
              const GLfloat modelMatrix[16],
              const GLfloat projMatrix[16],
              const GLint viewport[4],
              GLclampf nearVal, GLclampf farVal,
              GLfloat *objx, GLfloat *objy, GLfloat *objz,
              GLfloat *objw);

void
gluPickMatrix(GLfloat x, GLfloat y, GLfloat deltax, GLfloat deltay,
              GLint viewport[4]);

#endif