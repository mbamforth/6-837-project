#include "MatrixStack.h"


// Initializes to the identity matrix
MatrixStack::MatrixStack()
{
	Matrix4f iden;
	iden.setCol( 0, Vector4f( 1.0, 0.0, 0.0, 0.0 ) );
        iden.setCol( 1, Vector4f( 0.0, 1.0, 0.0, 0.0 ) );
        iden.setCol( 2, Vector4f( 0.0, 0.0, 1.0, 0.0 ) );
        iden.setCol( 3, Vector4f( 0.0, 0.0, 0.0, 1.0 ) );
	m_matrices.push_back(iden);
}

// Reverts stack to just the identity matrix
void MatrixStack::clear()
{
	m_matrices.clear();
	Matrix4f iden;
	iden.setCol( 0, Vector4f( 1.0, 0.0, 0.0, 0.0 ) );
        iden.setCol( 1, Vector4f( 0.0, 1.0, 0.0, 0.0 ) );
        iden.setCol( 2, Vector4f( 0.0, 0.0, 1.0, 0.0 ) );
        iden.setCol( 3, Vector4f( 0.0, 0.0, 0.0, 1.0 ) );
	m_matrices.push_back(iden);
}

// Returns the top of the stack
Matrix4f MatrixStack::top()
{
	Matrix4f top;
	top = m_matrices.back();
	return top;
}

// Pushes m onto the stack.
// Your stack should have OpenGL semantics:
// the new top should be the old top multiplied by m
void MatrixStack::push( const Matrix4f& m )
{
	Matrix4f top;
	top = m_matrices.back();
	Matrix4f newTop;
	newTop = top*m;
	m_matrices.push_back(newTop);
}

// Pops the top matrix
void MatrixStack::pop()
{
	m_matrices.pop_back();
}
