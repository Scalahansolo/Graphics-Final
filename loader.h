#ifndef LOADER_H
#define LOADER_H

#ifdef _cplusplus
class Model_OBJ
{
  public:
    Model_OBJ();
    float* Model_OBJ::calculateNormal(float* coord1,float* coord2,float* coord3 );
    int Model_OBJ::Load(char *filename);  // Loads the model
    void Model_OBJ::Draw();         // Draws the model on the screen
    void Model_OBJ::Release();        // Release the model

    float* normals;             // Stores the normals
    float* Faces_Triangles;         // Stores the triangles
    float* vertexBuffer;          // Stores the points which make the object
    long TotalConnectedPoints;        // Stores the total number of connected verteces
    long TotalConnectedTriangles;     // Stores the total number of connected triangles

};
#endif /* __cplusplus */

#ifdef _cplusplus
extern "C" {
#endif
    struct Model_OBJ;

    Model_OBJ* Model_OBJ_new();
    void Model_OBJ_delete(Model_OBJ*self);

    float* Model_OBJ_calculateNormal(Model_OBJ*self,float*coord1,float*coord2,float*coord3);
    int Model_OBJ_Load(Model_OBJ*self,char*filename); // Loads the model
    void Model_OBJ_Draw(Model_OBJ*self); // Draws the model on the screen
    void Model_OBJ_Release(Model_OBJ*self); // Draws the model on the screen

#ifdef _cplusplus
}
#endif

#endif /* LOADER_H */