# DiarioOpenGL - Como carregar modelos
- Importar a biblioteca assimp.
- Remover os vertices, o VBO, VAO e as texturas, da main.cpp.
- Criar classe Mesh, para carregar e configurar as malhas.
- Criar classe Model, para ler o arquivo do modelo, verificar os erros, separar os dados e desenhar o modelo.
- Atualizar os shaders.
- Importar e carregar um modelo de mochila com o formato .obj (Object File Wavefront).
- Nota: por algum motivo, na versão 5.2.0 da assimp existe um bug na leitura de malhas complexas, demora muito. (pelo menos no windows)
- Corrigir o bug alterando o arquivo libs/assimp/code/AssetLib/Obj/ObjFileParser.cpp.
- Desenhar a mochila.
- <img src="https://user-images.githubusercontent.com/73361955/181652822-03e8e5a7-c379-4da4-9cff-943e29ea6957.png" width="320" height="240">
- Renomear os shaders para model_fragment.glsl e model_vertex.glsl.
- Importar e carregar um modelo de cubo.
- Criar shaders para a lâmpada.
- Usar esses shaders e desenhar uma lâmpada com formato de cubo ao lado da mochila.
- Adicionar uma iluminação ambiente na mochila.
- Adicionar normal e fragment position aos shaders.
- Adicionar uma iluninação difusa na mochila.
- Rotacionar a mochila.
- Adicionar uma matriz normal no vertex shader para corrigir a iluminação.
- Remover a rotação da mochila.
- Mover a lâmpada ao redor da mochila ao longo do tempo.
- Adicionar uma iluminação especular.
- <img src="https://user-images.githubusercontent.com/73361955/181683984-0f8a4de9-6421-402b-90cf-de577567454f.gif" width="320" height="240">
- Nota: alterar as propriedades do material pode ser muito interessante.
