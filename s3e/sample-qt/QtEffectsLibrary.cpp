
#include "QtEffectsLibrary.h"
#include "TLFXPugiXMLLoader.h"

#include <QOpenGLTexture>
#include <QImage>

#include <stdint.h>
#include <cmath>

TLFX::XMLLoader* QtEffectsLibrary::CreateLoader() const
{
    return new TLFX::PugiXMLLoader(0);
}

QtImage* QtEffectsLibrary::CreateImage() const
{
    return new QtImage();
}



bool QtImage::Load( const char *filename )
{
    QOpenGLTexture *texture = new QOpenGLTexture(QImage(filename).mirrored());
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    return true;
}

QtImage::QtImage()
    : _texture(NULL)
{

}

QtImage::~QtImage()
{
    if (_texture)
        delete _texture;
}

QOpenGLTexture* QtImage::GetTexture() const
{
    return _texture;
}

QtParticleManager::QtParticleManager( int particles /*= particleLimit*/, int layers /*= 1*/ )
    : TLFX::ParticleManager(particles, layers)
    , _lastSprite(NULL)
    , _lastAdditive(true)
{

}

void QtParticleManager::DrawSprite( QtImage* sprite, float px, float py, float frame, float x, float y, float rotation, float scaleX, float scaleY, unsigned char r, unsigned char g, unsigned char b, float a , bool additive )
{
    Q_ASSERT(frame == 0);

    unsigned char alpha = (unsigned char)(a * 255);
    if (alpha == 0 || scaleX == 0 || scaleY == 0) return;

    if (sprite != _lastSprite || additive != _lastAdditive)
        Flush();

    //uvs[index + 0] = {0, 0};
    batch.appendTexCoord(QVector2D(0, 0));
    //uvs[index + 1] = {1.0f, 0}
    batch.appendTexCoord(QVector2D(1.0, 0));
    //uvs[index + 2] = {1.0f, 1.0f};
    batch.appendTexCoord(QVector2D(1.0, 1.0));
    //uvs[index + 3] = {0, 1.0f};
    batch.appendTexCoord(QVector2D(0, 1.0));

    /*
    verts[index + 0].x = px - x * scaleX;
    verts[index + 0].y = py - y * scaleY;
    //verts[index + 0].z = 1.0f;
    verts[index + 1].x = verts[index + 0].x + _lastSprite->GetWidth() * scaleX;
    verts[index + 1].y = verts[index + 0].y;
    //verts[index + 1].z = 1.0f;
    verts[index + 2].x = verts[index + 1].x;
    verts[index + 2].y = verts[index + 1].y + _lastSprite->GetHeight() * scaleY;
    //verts[index + 2].z = 1.0f;
    verts[index + 3].x = verts[index + 0].x;
    verts[index + 3].y = verts[index + 2].y;
    //verts[index + 3].z = 1.0f;
    */

    float x0 = -x * scaleX;
    float y0 = -y * scaleY;
    float x1 = x0;
    float y1 = (-y + _lastSprite->GetHeight()) * scaleY;
    float x2 = (-x + _lastSprite->GetWidth()) * scaleX;
    float y2 = y1;
    float x3 = x2;
    float y3 = y0;

    float cos = cosf(rotation / 180.f * (float)M_PI);
    float sin = sinf(rotation / 180.f * (float)M_PI);

    //verts[index + 0] = {px + x0 * cos - y0 * sin, py + x0 * sin + y0 * cos};
    //verts[index + 0].z = 1.0f;
    batch.appendVertex(QVector3D(px + x0 * cos - y0 * sin, py + x0 * sin + y0 * cos, 0));
    //verts[index + 1] = {px + x1 * cos - y1 * sin, py + x1 * sin + y1 * cos};
    //verts[index + 1].z = 1.0f;
    batch.appendVertex(QVector3D(px + x1 * cos - y1 * sin, py + x1 * sin + y1 * cos, 0));
    //verts[index + 2] = {px + x2 * cos - y2 * sin, py + x2 * sin + y2 * cos};
    //verts[index + 2].z = 1.0f;
    batch.appendVertex(QVector3D(px + x2 * cos - y2 * sin, py + x2 * sin + y2 * cos, 0));
    //verts[index + 3] = {px + x3 * cos - y3 * sin, py + x3 * sin + y3 * cos};
    //verts[index + 3].z = 1.0f;
    batch.appendVertex(QVector3D(px + x3 * cos - y3 * sin, py + x3 * sin + y3 * cos, 0));

    for (int i = 0; i < 4; ++i) 
    {
        batch.appendColor(QColor(r, g, b, alpha));
    }
    
    _lastSprite = sprite;
    _lastAdditive = additive;
}

void QtParticleManager::Flush()
{
    if (batch.count() && _lastSprite)
    {
        _lastSprite->GetTexture()->bind();
        glDisable(GL_DEPTH);
        if (_lastAdditive) {
            // ALPHA_ADD
            glBlendEquationEXT( GL_FUNC_ADD );
            glBlendFunc( GL_SRC_ALPHA, GL_ONE );
        } else {
            // ALPHA_BLEND
            glBlendEquationEXT( GL_FUNC_ADD );
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        }

        batch.draw(&painter, 0, batch.count());
        batch.clear();
    }
}
