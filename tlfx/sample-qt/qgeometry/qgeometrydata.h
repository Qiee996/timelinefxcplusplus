#ifndef QGEOMETRYDATA_H
#define QGEOMETRYDATA_H

#include "qcolor4ub.h"
#include "qglnamespace.h"
#include "qglindexbuffer.h"
#include "qglvertexbundle.h"
#include "qglattributevalue.h"
#include "qcustomdataarray.h"
#include "qgeometry3d.h"
#include "qarray.h"

QT_BEGIN_NAMESPACE

class QGeometryDataPrivate;
class QLogicalVertex;
class QGLPainter;

namespace QGL
{
    inline quint32 fieldMask(QGL::VertexAttribute f) { return 1U << f; }

#if defined(QT_OPENGL_ES)
    typedef QArray<ushort> IndexArray;
#else
    typedef QArray<uint> IndexArray;
#endif
}

class QGeometryData
{
public:
    QGeometryData();
    QGeometryData(const QGeometryData &);
    QGeometryData(quint32 fields);
    ~QGeometryData();

    QGeometryData &operator=(const QGeometryData &);

    void appendGeometry(const QGeometryData &data);
    int appendVertex(const QLogicalVertex &v);
    void normalizeNormals();
    QBox3D boundingBox() const;
    QVector3D center() const;

    QGeometryData reversed() const;
    QGeometryData translated(const QVector3D &) const;
    void generateTextureCoordinates(Qt::Orientation orientation = Qt::Horizontal,
                                    QGL::VertexAttribute attribute = QGL::TextureCoord0);
    QGeometryData interleavedWith(const QGeometryData &other) const;
    void interleaveWith(const QGeometryData &other);
    void clear();
    void clear(QGL::VertexAttribute);
    void reserve(int amount);
    void draw(QGLPainter *painter, int start, int count, GLenum mode = QGL::Triangles, float drawWidth = 1.0f);
    bool upload();
    enum BufferStrategyFlags
    {
        InvalidStrategy     = 0x00,
        KeepClientData      = 0x01,
        BufferIfPossible    = 0x02,
    };
    Q_DECLARE_FLAGS(BufferStrategy, BufferStrategyFlags)
    void setBufferStrategy(BufferStrategy strategy);
    BufferStrategy bufferStrategy() const;
    QGLVertexBundle vertexBundle() const;
    QGLIndexBuffer indexBuffer() const;

    void appendIndex(int index);
    void appendIndices(int index1, int index2, int index3);
    void appendIndices(const QGL::IndexArray &indices);
    QGL::IndexArray indices() const;

    void appendVertex(const QVector3D &v0);
    void appendVertex(const QVector3D &v0, const QVector3D &v1);
    void appendVertex(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2);
    void appendVertex(const QVector3D &v0, const QVector3D &v1, const QVector3D &v2, const QVector3D &v3);

    void appendAttribute(float a, QGL::VertexAttribute field = QGL::CustomVertex0);
    void appendAttribute(float a, float b, QGL::VertexAttribute field = QGL::CustomVertex0);
    void appendAttribute(float a, float b, float c, QGL::VertexAttribute field = QGL::CustomVertex0);
    void appendAttribute(float a, float b, float c, float d, QGL::VertexAttribute field = QGL::CustomVertex0);
    void appendAttribute(const QVector2D &a, QGL::VertexAttribute field = QGL::CustomVertex0);
    void appendAttribute(const QVector3D &a, QGL::VertexAttribute field = QGL::CustomVertex0);
    void appendAttribute(const QVariant &a, QGL::VertexAttribute field = QGL::CustomVertex0);

    void appendNormal(const QVector3D &n0);
    void appendNormal(const QVector3D &n0, const QVector3D &n1);
    void appendNormal(const QVector3D &n0, const QVector3D &n1, const QVector3D &n2);
    void appendNormal(const QVector3D &n0, const QVector3D &n1, const QVector3D &n2, const QVector3D &n3);

    void appendTexCoord(const QVector2D &t0, QGL::VertexAttribute field = QGL::TextureCoord0);
    void appendTexCoord(const QVector2D &t0, const QVector2D &t1, QGL::VertexAttribute field = QGL::TextureCoord0);
    void appendTexCoord(const QVector2D &t0, const QVector2D &t1, const QVector2D &t2, QGL::VertexAttribute field = QGL::TextureCoord0);
    void appendTexCoord(const QVector2D &t0, const QVector2D &t1, const QVector2D &t2, const QVector2D &t3, QGL::VertexAttribute field = QGL::TextureCoord0);

    void appendColor(const QColor4ub &c0);
    void appendColor(const QColor4ub &c0, const QColor4ub &c1);
    void appendColor(const QColor4ub &c0, const QColor4ub &c1, const QColor4ub &c2);
    void appendColor(const QColor4ub &c0, const QColor4ub &c1, const QColor4ub &c2, const QColor4ub &c3);

    void appendVertexArray(const QVector3DArray &ary);
    void appendAttributeArray(const QCustomDataArray &ary, QGL::VertexAttribute field = QGL::CustomVertex0);
    void appendNormalArray(const QVector3DArray &ary);
    void appendTexCoordArray(const QVector2DArray &ary, QGL::VertexAttribute field = QGL::TextureCoord0);
    void appendColorArray(const QArray<QColor4ub> &ary);

    QLogicalVertex logicalVertexAt(int i) const;

    QVector3DArray vertices() const;
    QVector3D &vertex(int i);
    const QVector3D &vertexAt(int i) const;

    QVector3DArray normals() const;
    QVector3D &normal(int i);
    const QVector3D &normalAt(int i) const;

    QArray<QColor4ub> colors() const;
    QColor4ub &color(int i);
    const QColor4ub &colorAt(int i) const;

    QVector2DArray texCoords(QGL::VertexAttribute field = QGL::TextureCoord0) const;
    QVector2D &texCoord(int i, QGL::VertexAttribute field = QGL::TextureCoord0);
    const QVector2D &texCoordAt(int i, QGL::VertexAttribute field = QGL::TextureCoord0) const;

    float &floatAttribute(int i, QGL::VertexAttribute field = QGL::CustomVertex0);
    QVector2D &vector2DAttribute(int i, QGL::VertexAttribute field = QGL::CustomVertex0);
    QVector3D &vector3DAttribute(int i, QGL::VertexAttribute field = QGL::CustomVertex0);
    QCustomDataArray attributes(QGL::VertexAttribute field = QGL::CustomVertex0) const;
    float floatAttributeAt(int i, QGL::VertexAttribute field = QGL::CustomVertex0) const;
    QVector2D vector2DAttributeAt(int i, QGL::VertexAttribute field = QGL::CustomVertex0) const;
    QVector3D vector3DAttributeAt(int i, QGL::VertexAttribute field = QGL::CustomVertex0) const;

    QGLAttributeValue attributeValue(QGL::VertexAttribute field) const;
    bool hasField(QGL::VertexAttribute field) const;
    void enableField(QGL::VertexAttribute field);
    quint32 fields() const;
    int count() const;
    int count(QGL::VertexAttribute field) const;
    int indexCount() const;
    bool operator==(const QGeometryData &other) const;
    bool isEmpty() const;
    bool isNull() const;
    void detach();
#ifndef QT_NO_DEBUG
    quint64 id() const { return quint64(d); }
#endif
protected:
    const QVector3DArray *vertexData() const;
private:
    void create();
#ifndef QT_NO_DEBUG
    void check() const;
#else
    void check() const {}
#endif
    friend class QLogicalVertex;

    QGeometryDataPrivate *d;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QGeometryData::BufferStrategy)

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QGeometryData &vertices);
#endif

QT_END_NAMESPACE

#endif // QGEOMETRYDATA_H
