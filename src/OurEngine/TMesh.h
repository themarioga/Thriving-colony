#ifndef TMESH_H
#define TMESH_H

#include "TEntity.h"
#include <GL/glew.h>
#include "TResourceMesh.h"
#include <IOEngine/IO.h>

class TMesh : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TMesh();

        /**
         * @brief 
         * 
         */
        virtual ~TMesh();

        /**
         * @brief 
         * @param 
         */
        void loadMesh(TResourceMesh *);

        /**
         * @brief 
         * 
         */
        virtual void beginDraw();

        /**
         * @brief 
         * 
         */
        virtual void endDraw();

    private:
        TResourceMesh* mesh;

        GLuint vertexbuffer;
        GLuint normalbuffer;
        GLuint uvbuffer;
	    GLuint elementbuffer;
};

#endif