appuntes sobre render
vamos a tener tatnos rayos como px tiene nuestro campo de vision

1. necesito calcular el angulo de cada rayo
me interesa saber la mitad del angulo de viison si es 60 sera 30

si tenemoms un campo de vision e 6 px a 60 grados 
cada rayo tendra un angulo de 60 / 6px = 10 rayos

angulo = amgulo * (mathpi  / 180)

le pasamos despues 
connvertir en radianes 
campo de vision entre angulo --- 60 / 10 rayos

empeamos a hacer rayos desde la posicion del jugador
que es el angulo de rotacion menos 60 / 2

calcular la distancia de cada rayo hasta el punto de colision
esto esta calcualdo en distancia horizontal y distancia vertical --  guradarlo en una estructura

necesito la tangente para saber como de lejos esta el jugador con la colision, la linea recta