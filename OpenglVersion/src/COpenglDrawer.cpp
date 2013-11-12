#include "COpenglDrawer.h"
#include "gl\glew.h"
namespace xc{
	namespace drawBasement{

		void COpenglDrawer::draw(IDrawBuffer* vbuf,IDrawIndexBuffer* ibuf,IDrawCotext* context){
			vbuf->use(0);
			ibuf->use();
			GLenum type;
			switch (ibuf->getPrimityType())
			{
			case EPT_DOTS:
				type = GL_POINTS;
				break;
			case EPT_LINE_STRIP:
				type = GL_LINE_STRIP;
				break;
			case EPT_LINES:
				type = GL_LINES;
				break;
			case EPT_TRIANGLE_STRIP:
				type = GL_TRIANGLE_STRIP;
				break;
			case EPT_TRIANGLES:
				type = GL_TRIANGLES;
				break;
			default:
				return;
				break;
			}
			GLenum itype;
			switch (ibuf->getIndexType())
			{
			case EIT_UBYTE:
				itype = GL_UNSIGNED_BYTE;
				break;
			case EIT_UINT:
				itype = GL_UNSIGNED_INT;
				break;
			default:
				return;
				break;
			}
			glDrawElements(type,ibuf->getIndexNums(),itype,0);
			vbuf->unUse(0);
		}
	}
}