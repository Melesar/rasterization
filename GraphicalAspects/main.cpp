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
#include <Timer/timer.h>
#include <Parser/file_utils.h>

void buildAndRenderScene();

void test();

int main ()
{
	test();
	//buildAndRenderScene();
}

void test()
{
	FILE* f = fopen("obj-test.txt", "r");
	char line[LINE_LENGTH];

	while(readLine(f, line))
	{
		std::cout << line << std::endl;

		char token[3];
		char content[LINE_LENGTH - 3];
		getToken(line, token, content);

		std::cout << "Token: " << token << ", content: " << content << std::endl;

		float3 value;
		getFloat3(content, value);
		std::cout << "Value: " << value << std::endl;
	}
}

void buildAndRenderScene()
{
	Timer timer;
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

	timer.startSample("Textures creation");
	auto stoneTexture = Texture("stone.tga");
	auto wolfTexture = Texture("grass.tga");
	timer.finishSample();

	timer.startSample("Meshes creation");
	auto teapot = std::unique_ptr<Mesh>(Mesh::create("teapot.obj"));
	teapot->setTexture(&stoneTexture);

	auto wolf = std::unique_ptr<Mesh>(Mesh::create("Wolf.obj"));
	wolf->setTexture(&wolfTexture);

	auto sphere = std::unique_ptr<Mesh>(Mesh::create("sphere.OBJ"));
	sphere->setColor({1.f, 0.f, 0.f});
	timer.finishSample();

	timer.startSample("Meshes rendering");
	vp.setIdentity();
	vp.multByScale({0.5f, 0.5f, 0.5f});
	vp.multByRotation({1, 0, 0}, -90.f);
	vp.multByTranslation({ 5.f, -1.f, -15 });
	teapot->draw(rastr, vp);

	vp.setIdentity();
	vp.multByScale({1.5f, 1.5f, 1.5f});
	vp.multByRotation({0, 1.f, 0}, 90.f);
	vp.multByTranslation({-0.5f, -0.6f, -2.f});
	wolf->draw(rastr, vp);

	vp.setIdentity();
	vp.multByScale({0.8f, 0.8f, 0.8f});
	vp.multByTranslation({0.f, 1.5f, -5.f});
	sphere->draw(rastr, vp);
	timer.finishSample();

	auto cube = CubeMesh({2, 2, 2});
	cube.setColor({1, -0.5f, 0});

	auto cylinder = CylinderMesh({0, 0, 0}, 4, 6, 16);
	cylinder.setColor({0, 0, 1});

	timer.startSample("Primitives rendering");

	vp.setIdentity();
	vp.multByScale({0.3f, 0.3f, 0.3f});
	vp.multByRotation({0, 1.f, 0}, 45.f);
	vp.multByTranslation({-6.f, 4.f, -20.f});
	cube.draw(rastr, vp);

	vp.setIdentity();
	vp.multByScale({0.5f, 0.5f, 0.5f});
	vp.multByRotation({0, 1.f, 0}, 60.f);
	vp.multByTranslation({-6.f, -8.f, -20.f});
	cube.draw(rastr, vp);

	vp.setIdentity();
	vp.multByTranslation({4, -6.f, -15.f});
	cylinder.draw(rastr, vp);
	timer.finishSample();

	buff.save("f.tga");
}