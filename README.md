# Taller de Programación - TP3

**Alumno**: Fernando Fabbiano

**Padrón**: 102464

**URL**: https://github.com/FerFabbiano/tp3

**Versionado Semántico**: https://semver.org/lang/es/

1. **Descripción del trabajo**

	Este es un trabajo en el que hay tareas que deben ser realizadas en paralelo, luego debo trabajar con multithreads. Como plantiee el problema, tengo 2+n hilos, donde n es la cantidad de jugadores que están jugando al mismo tiempo, es decir la cantidad de clientes conectados a mi servidor. 
	Tengo un hilo main, que estará pendiente de cuando el servidor quiere dejar de prestar sus servicios, y prohibir que se conecten mas jugadores. En este caso, es un servidor educado, y permitirá a los jugadores actuales que terminen su partida. A su vez, este thread será el encargado de bindear el socket a través del cual se comunicará con los clientes, y se ocupará de lanzar el thread Aceptador, y posteriormente de liberar los recursos correspondientes al mismo. 
	El hilo Aceptador, como bien dice su nombre, aceptará nuevas conexiones de clientes que quieran jugar. Por cada cliente que acepta, lanza un nuevo thread (ThClient). A este nuevo cliente, se le asigna un número elegido de una lista que recibe el servidor, contra el que comparará los números que ingresa el cliente en su consola. 
	Luego de aceptar un nuevo cliente, el hilo Aceptador hace un seguimiento del estado en el que se encuentran los jugadores aceptados previamente. Si alguno de estos ya finalizó su partida, ya sea que ganó o perdió, libera sus recursos y finaliza ese hilo. De esta forma evitamos que se esten utilizando recursos en un hilo que no esta haciendo nada. 
	Es importante, al iniciar el trabajo, poder identificar cuáles son los recursos que van a ser accedidos por mas de un hilo, para evitar tener race conditions. Primero, tenemos los contadores de ganadores y perdedores. Cuando un jugador termina su partido, ThClient accede a alguno de estos dos objetos, y lo incrementa. Puede suceder que dos jugadores hayan terminado casi al mismo tiempo, y que el resultado de sus partidas sea el mismo, y por ende intenten incrementar la variable al mismo tiempo, generandose una race condition que pueda traernos problemas a la hora de saber el resultado final. Luego, tenemos las variables booleandas de ThAcceptor, keep_accepting y push. Ambas son accedidas tanto por el mismo hilo que las declara, como por el hilo main a través de una función. Cuando el servidor desea dejar de prestar servicios, estos dos booleanos son seteados en falso, para permitir que el hilo Aceptador liberé sus recursos de una forma correcta y ordenada. Para solucionar las posibles race conditions en este caso, use objetos atómicos de la librería estándar de c++, que aseguran un acceso seguro en estos casos. 

<p align="center">
<img src="https://user-images.githubusercontent.com/38590805/82852257-d876a480-9ed8-11ea-8fa2-c2c6e334af61.png" 			width=900 height=300>

	
