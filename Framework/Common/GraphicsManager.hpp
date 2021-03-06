#pragma once
#include <vector>
#include <memory>
#include "cbuffer.h"
#include "GfxConfiguration.hpp"
#include "FrameStructure.hpp"
#include "IRuntimeModule.hpp"
#include "IShaderManager.hpp"
#include "geommath.hpp"
#include "Image.hpp"
#include "Scene.hpp"
#include "Polyhedron.hpp"
#include "IDrawPass.hpp"
#include "IDispatchPass.hpp"

namespace My {
    class GraphicsManager : implements IRuntimeModule
    {
    public:
        virtual ~GraphicsManager() = default;

        int Initialize() override;
        void Finalize() override;

        void Tick() override;

        virtual void Draw();
        virtual void Present() {}

        virtual void ResizeCanvas(int32_t width, int32_t height);

        virtual void UseShaderProgram(const IShaderManager::ShaderHandler shaderProgram) {}

        virtual void DrawBatch(const std::vector<std::shared_ptr<DrawBatchContext>>& batches) {}

        virtual int32_t GenerateCubeShadowMapArray(const uint32_t width, const uint32_t height, const uint32_t count) { return 0; }
        virtual int32_t GenerateShadowMapArray(const uint32_t width, const uint32_t height, const uint32_t count) { return 0; }
        virtual void BeginShadowMap(const Light& light, const int32_t shadowmap, const uint32_t width, const uint32_t height, const int32_t layer_index) {}
        virtual void EndShadowMap(const int32_t shadowmap, const int32_t layer_index) {}
        virtual void SetShadowMaps(const Frame& frame) {}
        virtual void DestroyShadowMap(int32_t& shadowmap) {}

        // skybox
        virtual void DrawSkyBox() {}

        // terrain
        virtual void DrawTerrain() {}

        virtual int32_t GenerateTexture(const char* id, const uint32_t width, const uint32_t height) { return 0; }
        virtual void BeginRenderToTexture(int32_t& context, const int32_t texture, const uint32_t width, const uint32_t height) {}
        virtual void EndRenderToTexture(int32_t& context) {}

        virtual int32_t GenerateAndBindTextureForWrite(const char* id, const uint32_t slot_index, const uint32_t width, const uint32_t height) { return 0; }
        virtual void Dispatch(const uint32_t width, const uint32_t height, const uint32_t depth) {}

        virtual int32_t GetTexture(const char* id) { return 0; }

        virtual void DrawFullScreenQuad() {}

#ifdef DEBUG
        virtual void DrawPoint(const Point& point, const Vector3f& color) {}
        virtual void DrawPointSet(const PointSet& point_set, const Vector3f& color) {}
        virtual void DrawPointSet(const PointSet& point_set, const Matrix4X4f& trans, const Vector3f& color) {}
        virtual void DrawLine(const Point& from, const Point& to, const Vector3f &color) {}
        virtual void DrawLine(const PointList& vertices, const Vector3f &color) {}
        virtual void DrawLine(const PointList& vertices, const Matrix4X4f& trans, const Vector3f &color) {}
        virtual void DrawTriangle(const PointList& vertices, const Vector3f &color) {}
        virtual void DrawTriangle(const PointList& vertices, const Matrix4X4f& trans, const Vector3f &color) {}
        virtual void DrawTriangleStrip(const PointList& vertices, const Vector3f &color) {}
        virtual void DrawTextureOverlay(const int32_t texture, const float vp_left, const float vp_top, 
                                const float vp_width, const float vp_height) {}
        virtual void DrawTextureArrayOverlay(const int32_t texture, const float layer_index, 
                                     const float vp_left, const float vp_top, const float vp_width, const float vp_height) {}
        virtual void DrawCubeMapOverlay(const int32_t cubemap, const float vp_left, const float vp_top, 
                                const float vp_width, const float vp_height, const float level) {}
        virtual void DrawCubeMapArrayOverlay(const int32_t cubemap, const float layer_index, 
                                     const float vp_left, const float vp_top, const float vp_width, const float vp_height, 
                                     const float level) {}
        virtual void ClearDebugBuffers() {}

        void DrawEdgeList(const EdgeList& edges, const Vector3f& color);
        void DrawPolygon(const Face& face, const Vector3f& color);
        void DrawPolygon(const Face& face, const Matrix4X4f& trans, const Vector3f& color);
        void DrawPolyhydron(const Polyhedron& polyhedron, const Vector3f& color);
        void DrawPolyhydron(const Polyhedron& polyhedron, const Matrix4X4f& trans, const Vector3f& color);
        void DrawBox(const Vector3f& bbMin, const Vector3f& bbMax, const Vector3f& color);
#endif

    protected:
        virtual void BeginScene(const Scene& scene);
        virtual void EndScene();

        virtual void BeginFrame(const Frame& frame) {}
        virtual void EndFrame() {}

        virtual void BeginPass() {}
        virtual void EndPass() {}

        virtual void BeginCompute() {}
        virtual void EndCompute() {}

        virtual void initializeGeometries(const Scene& scene) {}
        virtual void initializeSkyBox(const Scene& scene) {}
        virtual void initializeTerrain(const Scene& scene) {}

#ifdef DEBUG
        virtual void RenderDebugBuffers() {}
#endif

    private:
        void InitConstants() {}
        void CalculateCameraMatrix();
        void CalculateLights();

        void UpdateConstants();

    protected:
        uint32_t m_nFrameIndex = 0;

        std::vector<Frame>  m_Frames;
        std::vector<std::shared_ptr<IDispatchPass>> m_InitPasses;
        std::vector<std::shared_ptr<IDrawPass>> m_DrawPasses;

        constexpr static float skyboxVertices[24] = {
            1.0f,  1.0f,  1.0f,  // 0
            -1.0f,  1.0f,  1.0f,  // 1
            1.0f, -1.0f,  1.0f,  // 2
            1.0f,  1.0f, -1.0f,  // 3
            -1.0f,  1.0f, -1.0f,  // 4
            1.0f, -1.0f, -1.0f,  // 5
            -1.0f, -1.0f,  1.0f,  // 6
            -1.0f, -1.0f, -1.0f   // 7
        };

        constexpr static uint8_t skyboxIndices[36] = {
            4, 7, 5,
            5, 3, 4,

            6, 7, 4,
            4, 1, 6,

            5, 2, 0,
            0, 3, 5,

            6, 1, 0,
            0, 2, 6,

            4, 3, 0,
            0, 1, 4,

            7, 6, 5,
            5, 6, 2
        };
    };

    extern GraphicsManager* g_pGraphicsManager;
}

