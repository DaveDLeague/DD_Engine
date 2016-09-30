#include "Renderer3D.h"

Renderer3D::Renderer3D(Shader shader){
	this->shader = shader;
}
Renderer3D::~Renderer3D(){}

void Renderer3D::drawModel(Model &m, Camera c){
	this->shader.use();

	glm::mat4 modelView = glm::translate(glm::mat4(1.0f), m.position);
	modelView = glm::rotate(modelView, m.rotation.x, glm::vec3(1, 0, 0));
	modelView = glm::rotate(modelView, m.rotation.y, glm::vec3(0, 1, 0));
	modelView = glm::rotate(modelView, m.rotation.z, glm::vec3(0, 0, 1));	
	modelView = glm::scale(modelView, m.scale);	

	glm::mat4 camera = glm::lookAt(c.position, c.position + c.front, c.up);	

	glm::mat4 mvp = projection * camera * modelView;

	this->shader.setMatrix4("modelViewProjMatrix", mvp);

    glBindVertexArray(m.vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Renderer3D::initRenderData(){

}
