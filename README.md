# DiarioOpenGL
- Configurar o projeto com CMake.
- Importar a biblioteca GLFW.
- Criar uma janela.
- Importar a biblioteca GLAD.
- Carregar o contexto OpenGL e mudar o fundo da janela de cor.
- Criar função de retorno de chamada para redimensionamento de janela.
- Importar o código-fonte para Vertex e Fragment Shader.
- Criar programas para o Vertex e Fragment Shader e compilar.
- Criar Shader Program.
- Anexar esses Shaders criados ao Shader Program.
- Vincular Shader Program ao OpenGL.
- Verificar erros de vinculação.
- Deletar Vertex e Fragment Shader, pois foram anexados ao Shader Program e estão inutilizados.
- Configurar os dados dos vertices do triângulo.
- Criar VBO (Vertex Buffer Object), que de modo simplificado, tem como objetivo armazenar o buffer na memória da placa de vídeo, para melhorar o desempenho.
- Vincular VBO ao OpenGL.
- Copiar os dados dos vertices para o VBO.
- Criar VAO (Vertex Array Object), que de modo simplificado, tem como objetivo descrever como os vertices são armazenados no VBO.
- Vincular VAO ao OpenGL.
- Atribuir ponteiros para os vertices.
- Desvincular VBO e VAO para não modificar acidentalmente esses objetos.
- Definir qual Shader Program o OpenGL deve usar.
- Definir primitiva GL_TRIANGLES.
- Desenhar triângulo.
- Atualizar e adicionar mais um vertice aos vertices, para desenhar um retângulo, a partir de dois triângulos.
- Criar indices a partir dos vertices, para desenhar os triângulos sem repetir as coordenadas.
- Criar EBO (Element Buffer Object), que de modo simplificado, tem como objetivo armazenar um buffer com os indices dos vertices dos elementos.
- Desenhar retângulo.
- Criar classe Shader, e a partir disso, criar arquivos fragment_shader.glsl e vertex_shaders.glsl para serem lidos por essa classe.
- Instânciar a classe criada e usar os shaders.
- Adicionar três floats na sequência das coordenadas de cada vertice para indicar a cor.
- Configurar os ponteiros de vertices e cores para um tamanho de seis floats, pois os três primeiros indicam o vertice, e os três últimos indicam a cor.
- Importar imagem wall.jpg para servir de textura.
- Importar biblioteca stb_image para carregar o arquivo de imagem da textura.
- Adicionar coordenadas de textura para cada vertice.
- Configurar os ponteiros de vertices, cores e texturas, para um tamanho de oito floats, pois os três primeiros indicam o vertice, os três consequentes indicam a cor, e os dois últimos, a coordenada da textura.
- Alterar variável ID da classe Shader para public.
- Configurar as texturas nos shaders, ou seja, nos arquivos de código-fonte GLSL.
- Configurar a textura na main.cpp.
- Desenhar um retângulo texturizado.
- Importar GLM, uma biblioteca matemática, para facilitar os cálculos de matrizes e vetores.
- Remover os atributos de cor dos vértices, pois não serão mais usados.
- Criar uma matriz 4x4 para sofrer transformações, e depois, multiplicar ela pela matriz do objeto.
- Alterar a escala e rotacionar objeto ao longo do tempo.
- <img src="https://user-images.githubusercontent.com/73361955/175783078-024ede84-1723-427c-a60d-a36a7bd9d854.gif" width="300" height="200">
