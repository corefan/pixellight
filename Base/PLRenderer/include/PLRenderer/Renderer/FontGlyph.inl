/*********************************************************\
 *  File: FontGlyph.inl                                  *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRenderer {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the size (in pixel) of the glyph
*/
inline const PLMath::Vector2i &FontGlyph::GetSize() const
{
	return m_nSize;
}

/**
*  @brief
*    Returns the distance (in pixel) from the current pen position to the glyph bitmap
*/
inline const PLMath::Vector2 &FontGlyph::GetCorner() const
{
	return m_vCorner;
}

/**
*  @brief
*    Returns the object space pen advance
*/
inline const PLMath::Vector2 &FontGlyph::GetPenAdvance() const
{
	return m_vPenAdvance;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
