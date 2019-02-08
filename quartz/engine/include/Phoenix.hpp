#pragma once

#include <engine/core/Core.hpp>

#include <engine/core/Application.hpp>
#include <engine/core/EntryPoint.hpp>

// ----------- GRAPHICS ------------------------------------- //
#include <engine/core/graphics/IWindow.hpp>
#include <engine/core/graphics/gl/ShaderPipeline.hpp>
#include <engine/core/graphics/gl/TextureArray.hpp>
#include <engine/core/graphics/gl/VertexArray.hpp>
#include <engine/core/graphics/gl/VertexBuffer.hpp>
#include <engine/core/graphics/gl/VertexAttrib.hpp>

#include <engine/core/graphics/Camera.hpp>

// ----------- EVENTS ------------------------------------- //
#include <engine/core/events/Keys.hpp>

// ----------- MATHS ------------------------------------- //
#include <engine/core/math/Vector2.hpp>
#include <engine/core/math/Vector3.hpp>
#include <engine/core/math/Matrix4x4.hpp>
#include <engine/core/math/MathUtils.hpp>

// ----------- UTILITIES ------------------------------------- //
#include <engine/core/utils/Config.hpp>
#include <engine/core/utils/IO.hpp>
#include <engine/core/utils/Logging.hpp>

// ----------- VOXELS ------------------------------------- //
#include <engine/voxels/Block.hpp>
#include <engine/voxels/ChunkManager.hpp>
