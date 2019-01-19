#include <Light/light.h>
#include <Texture/texture.h>
#include "Buffer/TgaBuffer.h"
#include "Rasterizer/Rasterizer.h"
#include "Tests/main_tests.h"
#include "VertexProcessor/VertexProcessor.h"
#include "Mesh/TriangleMesh.h"
#include "Mesh/CubeMesh.h"
#include "Mesh/cone_mesh.h"
#include "Mesh/cylinder_mesh.h"
#include "utils.h"

int main ()
{
	TgaBuffer buff(512, 512);

	VertexProcessor vp;
	vp.setPerspective(60, 1.f, 1.f, 50.f);
	vp.setLookat({ 0, 0, -10 }, { 0, 0, 0 }, { 0, 1, 0 });

	Rasterizer rastr(&buff);

	vp.setIdentity();
	vp.multByTranslation({0.f, 0.f, -1});
	DirectionalLight dirLight (vp);
	dirLight.ambient = {};
	dirLight.specular = {0.4, 0.4, 0.4};
	dirLight.diffuse = {0.3, 0.3, 0.3};
	rastr.addLight(&dirLight);

	auto stoneTexture = Texture("stone.tga");
	auto wolfTexture = Texture("grass.tga");
	wolfTexture.save("texture_test.tga");

	auto teapot = std::unique_ptr<Mesh>(Mesh::create("teapot.obj"));
	vp.setIdentity();
	vp.multByScale({0.5f, 0.5f, 0.5f});
	vp.multByRotation({1, 0, 0}, -90.f);
	vp.multByTranslation({ 5.f, -1.f, -15 });
	teapot->setTexture(&stoneTexture);
	teapot->draw(rastr, vp);

	auto wolf = std::unique_ptr<Mesh>(Mesh::create("Wolf.obj"));
	vp.setIdentity();
	vp.multByScale({1.5f, 1.5f, 1.5f});
	vp.multByRotation({0, 1.f, 0}, 90.f);
	vp.multByTranslation({-0.5f, -0.6f, -2.f});
	wolf->setTexture(&wolfTexture);
	wolf->draw(rastr, vp);

	auto cube = CubeMesh({2, 2, 2});
	vp.setIdentity();
	vp.multByScale({0.3f, 0.3f, 0.3f});
	vp.multByRotation({0, 1.f, 0}, 45.f);
	vp.multByTranslation({0.f, 4.f, -20.f});
	cube.setColor({1, -0.5f, 0});
	cube.draw(rastr, vp);

    vp.setIdentity();
    vp.multByScale({0.5f, 0.5f, 0.5f});
    vp.multByRotation({0, 1.f, 0}, 60.f);
    vp.multByTranslation({-6.f, -8.f, -20.f});
    cube.draw(rastr, vp);

	auto cone = ConeMesh(3, 4);
	vp.setIdentity();
	vp.multByTranslation({7, 5, -20});
	cone.setColor({0, 1, 0});
	cone.draw(rastr, vp);

	vp.setIdentity();
	vp.multByRotation({0, 0.6f, 0.6f}, 57.f);
    vp.multByTranslation({-8, 4, -20});
    cone.draw(rastr, vp);

    auto cylinder = CylinderMesh({0, 0, 0}, 4, 6, 64);
    vp.setIdentity();
    vp.multByTranslation({4, -6.f, -15.f});
    cylinder.setColor({0, 0, 1});
    cylinder.draw(rastr, vp);

    buff.save("f.tga");
}