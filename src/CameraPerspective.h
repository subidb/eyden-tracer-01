// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"

/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{
public:
	/**
	 * @brief Constructor
	 * @param pos Camera origin (center of projection)
	 * @param dir Camera viewing direction
	 * @param up Up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
	 * @param resolution The image resolution
	 */
	CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)
		: ICamera(resolution)
		, m_pos(pos)
		, m_dir(dir)
		, m_up(up)
	{
		// --- PUT YOUR CODE HERE ---
		m_focus = 1 / tan((Pif * angle) / 360);
		m_yAxis = normalize(-1*m_up);
		m_xAxis = normalize(m_dir.cross(m_up));

		m_aspect = (float) resolution.width / resolution.height;

	}
	virtual ~CCameraPerspective(void) = default;

	virtual bool InitRay(float x, float y, Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---
		float ndcx = (float) (x + 0.5) / getResolution().width;
		float ndcy = (float) (y + 0.5) / getResolution().height;

		float sscx = (2 * ndcx - 1) * m_aspect;
		float sscy = 2 * ndcy - 1;

		ray.dir = normalize(m_dir * m_focus + sscx * m_xAxis + sscy * m_yAxis);
		ray.org = m_pos;
		ray.t = std::numeric_limits<float>::max();

		return true;
	}


private:
	// input values
	Vec3f m_pos;
	Vec3f m_dir;
	Vec3f m_up;

	// preprocessed values
	float m_focus;
	Vec3f m_xAxis;
	Vec3f m_yAxis;
	Vec3f m_zAxis;
	float m_aspect;
};