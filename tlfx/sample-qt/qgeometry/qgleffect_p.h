/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QGLEFFECT_P_H
#define QGLEFFECT_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qglpainter.h"
#include <QString>
#include <QMap>
#include <QColor>
#include <QScopedPointer.h>

QT_BEGIN_NAMESPACE

#if defined(QT_OPENGL_ES_2)
#define QGL_SHADERS_ONLY 1
#endif

class QGLPainter;
class QGLMaterial;
class QGLFlatColorEffectPrivate;
class QGLPerVertexColorEffectPrivate;
class QGLFlatTextureEffectPrivate;
class QGLFlatDecalTextureEffectPrivate;
class QGLVertColorTextureEffectPrivate;
class QGLLitMaterialEffectPrivate;
class QOpenGLShaderProgram;

class QGLFlatColorEffect : public QGLAbstractEffect
{
public:
    QGLFlatColorEffect();
    virtual ~QGLFlatColorEffect();

    bool supportsPicking() const;
    void setActive(QGLPainter *painter, bool flag);
    void update(QGLPainter *painter, QGLPainter::Updates updates);

private:
    QScopedPointer<QGLFlatColorEffectPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QGLFlatColorEffect)
    Q_DISABLE_COPY(QGLFlatColorEffect)
};

class QGLPerVertexColorEffect : public QGLAbstractEffect
{
public:
    QGLPerVertexColorEffect();
    virtual ~QGLPerVertexColorEffect();

    void setActive(QGLPainter *painter, bool flag);
    void update(QGLPainter *painter, QGLPainter::Updates updates);

private:
    QScopedPointer<QGLPerVertexColorEffectPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QGLPerVertexColorEffect)
    Q_DISABLE_COPY(QGLPerVertexColorEffect)
};

class QGLFlatTextureEffect : public QGLAbstractEffect
{
public:
    QGLFlatTextureEffect();
    virtual ~QGLFlatTextureEffect();

    void setActive(QGLPainter *painter, bool flag);
    void update(QGLPainter *painter, QGLPainter::Updates updates);

private:
    QScopedPointer<QGLFlatTextureEffectPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QGLFlatTextureEffect)
    Q_DISABLE_COPY(QGLFlatTextureEffect)
};

class QGLFlatDecalTextureEffect : public QGLAbstractEffect
{
public:
    QGLFlatDecalTextureEffect();
    virtual ~QGLFlatDecalTextureEffect();

    void setActive(QGLPainter *painter, bool flag);
    void update(QGLPainter *painter, QGLPainter::Updates updates);

private:
    QScopedPointer<QGLFlatDecalTextureEffectPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QGLFlatDecalTextureEffect)
    Q_DISABLE_COPY(QGLFlatDecalTextureEffect)
};

class QGLVertColorTextureEffect : public QGLAbstractEffect
{
public:
    QGLVertColorTextureEffect();
    virtual ~QGLVertColorTextureEffect();

    void setActive(QGLPainter *painter, bool flag);
    void update(QGLPainter *painter, QGLPainter::Updates updates);

private:
    QScopedPointer<QGLVertColorTextureEffectPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QGLVertColorTextureEffect)
    Q_DISABLE_COPY(QGLVertColorTextureEffect)
};

class QGLLitMaterialEffect : public QGLAbstractEffect
{
public:
    QGLLitMaterialEffect();
    virtual ~QGLLitMaterialEffect();

    void setActive(QGLPainter *painter, bool flag);
    void update(QGLPainter *painter, QGLPainter::Updates updates);

protected:
    QGLLitMaterialEffect
        (GLenum mode, const char *vshader, const char *fshader,
         const QString& programName);

private:
    QScopedPointer<QGLLitMaterialEffectPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QGLLitMaterialEffect)
    Q_DISABLE_COPY(QGLLitMaterialEffect)
};


class QGLLitTextureEffect : public QGLLitMaterialEffect
{
public:
    virtual ~QGLLitTextureEffect();

protected:
    QGLLitTextureEffect(GLenum mode, const char *vshader, const char *fshader,
                        const QString& programName);
};

class QGLLitDecalTextureEffect : public QGLLitTextureEffect
{
public:
    QGLLitDecalTextureEffect();
    virtual ~QGLLitDecalTextureEffect();
};

class QGLLitModulateTextureEffect : public QGLLitTextureEffect
{
public:
    QGLLitModulateTextureEffect();
    virtual ~QGLLitModulateTextureEffect();
};

class QGLColladaFxEffectPrivate
{
    friend class QGLColladaFxEffectFactory;
public:
    QGLColladaFxEffectPrivate();
    ~QGLColladaFxEffectPrivate();

    void addMaterialChannelsToShaderSnippets(const QGLMaterial *material);
    void resetGlueSnippets();
    void setTextureUniform(QOpenGLShaderProgram *program, QGLPainter* painter, QString channelName, QGLTexture2D* texture, int* textureUnit, QColor fallbackColor);
    void updateMaterialChannelSnippets(QString channelName, QGLTexture2D* texture, int* textureUnit, QColor fallbackColor);

    QString id;
    QString sid;
    QString name;

    // The spec allows for 3D textures as well, but for now only 2D is
    // supported
    QGLTexture2D* emissiveTexture;
    QGLTexture2D* ambientTexture;
    QGLTexture2D* diffuseTexture;
    QGLTexture2D* specularTexture;
    int lighting;
    QGLMaterial* material;

    QStringList vertexShaderCodeSnippets;
    QStringList vertexShaderDeclarationSnippets;
    QStringList vertexShaderVariableNames;

    QStringList fragmentShaderCodeSnippets;
    QStringList fragmentShaderDeclarationSnippets;
    QStringList fragmentShaderVariableNames;

    QString vertexShaderEndGlueSnippet;
    QString vertexShaderMainGlueSnippet;
    QString fragmentShaderEndGlueSnippet;
    QString fragmentShaderMainGlueSnippet;

    bool currentlyActive;
};

QT_END_NAMESPACE

#endif // QGLEFFECT_P_H
