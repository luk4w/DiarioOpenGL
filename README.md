# DiarioOpenGL
- Configurar o projeto com CMake.
- Importar a biblioteca GLFW.
- Criar uma janela.
- Importar a biblioteca GLAD.
- <a href="https://youtu.be/MvAavNh-f8w">Carregar o contexto OpenGL e mudar o fundo da janela de cor.
- <img src="https://user-images.githubusercontent.com/73361955/175784032-04498bba-fcf5-4d32-8be9-d05b8037c5a9.png" width="300" height="200"> <a>
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
- <a href="https://youtu.be/C2fJJhRKMl4">Desenhar um triângulo.
- <img src="https://user-images.githubusercontent.com/73361955/175783682-888e35d1-f695-41e1-88e7-4e2a8e02f174.png" width="300" height="200"><a>
- Atualizar e adicionar mais um vertice aos vertices, para desenhar um retângulo, a partir de dois triângulos.
- Criar indices a partir dos vertices, para desenhar os triângulos sem repetir as coordenadas.
- Criar EBO (Element Buffer Object), que de modo simplificado, tem como objetivo armazenar um buffer com os indices dos vertices dos elementos.
- <a href="https://youtu.be/X_hD_ea1D_E">Desenhar um retângulo.
- <img src="https://user-images.githubusercontent.com/73361955/175783783-35100de8-0262-4c82-b80a-c87a308bc2c4.png" width="300" height="200"><a>
- Criar classe Shader, e a partir disso, criar arquivos fragment_shader.glsl e vertex_shaders.glsl para serem lidos por essa classe.
- Instânciar a classe criada e usar os shaders.
- Adicionar três floats na sequência das coordenadas de cada vertice para indicar a cor.
- Configurar os ponteiros de vertices e cores para um tamanho de seis floats, pois os três primeiros indicam o vertice, e os três últimos indicam a cor.
- <a href="https://youtu.be/RmLedWWnYO4"><img src="https://user-images.githubusercontent.com/73361955/175819855-e7b0cd66-cbdf-46e7-833f-721cad542178.png" width="300" height="200"><a>
- Importar imagem wall.jpg para servir de textura.
- Importar biblioteca stb_image para carregar o arquivo de imagem da textura.
- Adicionar coordenadas de textura para cada vertice.
- Configurar os ponteiros de vertices, cores e texturas, para um tamanho de oito floats, pois os três primeiros indicam o vertice, os três consequentes indicam a cor, e os dois últimos, a coordenada da textura.
- Alterar variável ID da classe Shader para public.
- Configurar as texturas nos shaders, ou seja, nos arquivos de código-fonte GLSL.
- Configurar a textura na main.cpp.
- Desenhar um retângulo texturizado.
- <img src="https://user-images.githubusercontent.com/73361955/175783971-1b031f0e-6a61-4fe7-adcb-c0edfef96f27.png" width="300" height="200"> 
- Importar GLM, uma biblioteca matemática, para facilitar os cálculos de matrizes e vetores.
- Remover os atributos de cor dos vértices, pois não serão mais usados.
- Criar uma matriz 4x4 para sofrer transformações, e depois, multiplicar ela pela matriz do objeto.
- Alterar a escala e rotacionar o objeto ao longo do tempo.
- <img src="https://user-images.githubusercontent.com/73361955/176321672-407a4b85-2562-4c02-9624-bac3deff47ad.gif" width="300" height="200">
- Remover a alteração de escala.
- Mover o objeto (transladar) para o canto inferior direito e depois rotacionar.
- <img src="https://user-images.githubusercontent.com/73361955/176322487-df41c190-5693-4238-b8e3-b61e20643fd0.gif" width="300" height="200">
- Remover a matriz de transformação.
- Criar três matrizes identidades (Model, View e Projection) para realizar a projeção de perspectiva.
- Model Matrix: para transformar as coordenadas do modelo em coordenadas no mundo.
- View Matrix: transformar a visualização.
- Projection Matrix: espaço da câmera, o ângulo de abertura e a distância dos planos de corte de renderização.
- Aplicar rotação de -55° na Model Matrix, em relação ao eixo x. Isso modificará a angulação do objeto.
- Transladar em -3.0f no eixo z a View Matrix, ou seja, mover a visualização para trás. A visualização abrange todos os objetos do mundo.
- Determinar o campo de visão, a proporção de tela e o intervalo de renderização dos objetos no mundo, através da Projection Matrix.
- <img src="https://user-images.githubusercontent.com/73361955/176261937-18f583c2-b292-48b1-93cc-a0209850262e.png" width="300" height="200"> 
- Importar vertices do cubo.
- Remover o Element Buffer Object.
- Desenhar um cubo.
- <img src="https://user-images.githubusercontent.com/73361955/176320367-182c348d-cd1f-49d1-ac79-93a8ac02e3c9.gif" width="300" height="200">
- Habilitar o teste do buffer de profundidade e limpar o buffer de profundidade.
- <img src="https://user-images.githubusercontent.com/73361955/176321260-1d5a34e4-6680-4870-895f-020921d42c7c.gif" width="300" height="200"> 
- Definir uma posição para cada cubo no espaço do mundo.
- Criar um laço de repetição "for" dentro do loop de renderização principal, e dentro dele, instânciar um cubo para cada posição criada no espaço do mundo.
- Desenhar múltiplos cubos.
- <img src="https://user-images.githubusercontent.com/73361955/176333394-3acb7c49-0c24-41aa-9fe4-7e04b55306da.png" width="300" height="200"> 

