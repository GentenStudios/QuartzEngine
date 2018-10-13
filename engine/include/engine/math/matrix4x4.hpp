#pragma once

namespace phoenix {
	/**
	 * @brief Represents a column major 4x4 matrix of floats.
	 */
	struct Matrix4x4
	{
		float elements[4 * 4]; ///< The 16 float array that stores the matrices elements sequentially.

		/**
		 * @brief Default constructs the as an identity matrix (the top left to bottom right diagonal is 1.0f)
		 */
		Matrix4x4();
	};
}