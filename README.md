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
- Criar um laço de repetição "for" dentro do loop de renderização principal, e dentro dele, criar um cubo para cada posição definida.
- Desenhar múltiplos cubos.
- <img src="https://user-images.githubusercontent.com/73361955/176333394-3acb7c49-0c24-41aa-9fe4-7e04b55306da.png" width="300" height="200">
- Definir a Projection Matrix fora do loop de renderização principal.
- Transformar a View Matrix com a função lookAt, para ver as coordenadas dos vertices da perspectiva de uma câmera.
- <img src="https://user-images.githubusercontent.com/73361955/176566835-78f4f104-de2a-4e98-b264-12667ae5ef29.gif" width="300" height="200">
- Criar uma função para processar os comandos do teclado, e chamar essa função dentro do loop de renderização principal.
- Definir um sistema de três variáveis para movimentar a visualização em relação a câmera.
- Movimentar a visualização da perspectiva da câmera, através do teclado.
- Ajustar a velocidade do movimento através do deltaTime.
- O deltaTime pode ser definido como a diferença de tempo entre cada renderização.
- Definir uma função de retorno de chamada para o mouse.
- Movimentar a visualização da perspectiva da câmera, através do mouse.
- <img src="https://user-images.githubusercontent.com/73361955/177018740-232719dc-3e4e-4d01-8c17-92af5dc5365a.gif" width="300" height="200">
- Criar uma função de retorno de chamada para o scroll do mouse. 
- Definir o FOV como um parâmetro variável na Projection Matrix.
- Mover a Projection Matrix para dentro do loop de renderização principal.
- Aplicar zoom através do scroll do mouse.
- <img src="https://user-images.githubusercontent.com/73361955/177022233-7adeffd6-e229-43a0-b42d-d34d1f92d209.gif" width="300" height="200">
- Criar uma classe chamada Camera, para organizar o código, obter e atualizar a View Matrix, e processar os eventos de entrada do teclado e do mouse.
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
- Adicionar um mapa especular (specular map). para fazer com que determinadas partes do objeto brilhem mais ou menos que outras.
- <img src="https://user-images.githubusercontent.com/73361955/181841638-2ff6732d-d0ed-44fb-93ef-cef4531bdbb2.gif" width="320" height="240">
- Adicionar uma atenuação, que diminui a intensidade da luz no objeto com base na distância entre eles.
- Adicionar uma iluminação de lanterna, que basicamente é uma iluminação de holofote com a posição e a direção que a câmera está apontada.
- <img src="https://user-images.githubusercontent.com/73361955/181842380-cd75c035-5fda-4089-b51f-07919d5e030f.gif" width="320" height="240">
