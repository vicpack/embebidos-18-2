##Práctica 1: Uso de la Raspberry Pi 3 
#####Equipo 3: Bucio Segura Andrés, Valencia Páez José Eduardo.

----

La Raspberry Pi es un sistema embebido de tipo SoC (System on Chip) el cuál implementa el **Procesador Broadcom BCM2837** con el tamaño de una tarjeta de crédito cuyo propósito principal fue diseñado para el desarrollo educativo. 

>La meta del creador **Eben Upton** fué crear un sistema de bajo costo que pudiera ayudar a desarrollar las habilidades de programación y entendimiento de hardware a un nivel *pre-universitario*. 

>Pero debido a su tamaño tan pequeño y su precio accesible, fué rapidamente adoptado por creadores, emprendedores, y entusiastas de la electrónica para proyectos que requirieron más que un microcontrolador básico (tal como los dispositivos basados en *Arduino*).  [1] 

___

###Primeros pasos con la Raspberry Pi 3

En principio, para comenzar a usar la raspberry, necesitamos lo siguiente:

- 1 cable HDMI
- Memoria Micro SD Class 10 UHS-1 de 32GB
- Cargador de celular de 5V a 2A con salida micro-USB

Para cargar el sistema operativo que trabajará sobre la tarjeta tenemos 2 opciones documentadas de manera oficial en el sitio de raspberry. Puediendo hacer todo por terminal de Linux, o descargando un asistente que hace todo el proceso por nosotros llamado NOOBS (New Out Of the Box Software). [2]

Nosotros emplearemos el 'camino largo' haciendo el proceso desde la terminal linux. 

####Pasos
1. Descargamos la imagen de la última versión de Raspbian desde  [aquí](http://vx2-downloads.raspberrypi.org).

2.  Insertamos nuestra tarjeta micro SD a un puerto libre del computador. Y desmontamos todas las particiones introduciendo en la terminal la orden 

~~~
$sudo umount /dev/sdXY
~~~
Dónde X es la letra de la unidad (a, b, c, ...) y la Y el número de partición de la unidad (1, 2, 3, ...)

3. Copiamos la imagen del SO hacia la tarjeta SD con la órden: 
~~~
$sudo dd bs=4M if=2017-11-29-raspbian-stretch.img of=/dev/sdXY conv=fsync 
~~~

4. Desmontamos la imagen con: 
~~~
$sync
~~~

5. Procedemos a conectar un monitor, el cargador 5V a 2A, teclado y ratón para poder usarla como PC. 
![Figura1. Conectando y usando Raspberry](/home/eduardo/Documentos/Embedded_Linux/embebidos-18-2/practicas/prac1.UsoRasp/Equipo3/imagenes/1.jpg)
***Figura 1.** Conectando y usando la Raspberry*

###Usando la Raspberry Pi de manera remota 

Ahora procederemos a usar la raspberry usando una conexión remota, desde VNC, SSH y con un módulo Serie (FT232)

----
####Conexión por SSH
Lo primero que hay por hacer es configurar nuestra interfaz de red, en nuestro caso usaremos wlan. Modificaremos el archivo de configuración que almacena y gestiona las redes a las cuales nos podemos conectar, para acceder a el símplemente tecleamos en el terminal: 

~~~~
$ sudo nano /etc/wpa_supplicant/wpa_supplicant.conf
~~~~

Una vez abierto con nano, introducimos esta red, con la sintaxis adecuada. 

~~~~
network={
		ssid="Tenda_06DEC0"
		psk="MqZe5RY4"
		key_mgmt=WPA-PSK
		}
~~~~



![Figura2. Agregando la interfaz de red](/home/eduardo/Documentos/Embedded_Linux/embebidos-18-2/practicas/prac1.UsoRasp/Equipo3/imagenes/2018-02-19-220938_1366x768_scrot.png)
***Figura 2.** Agregando la interfaz de red "Tenda_06DEC0"*

Reiniciamos la Raspberry para que surtan efecto los cambios en el archivo.conf

Una vez encendida nuevamente, listaremos los demonios del sistema que están ejecutandose actualmente. Para ello, tecleamos el siguiente comando: 

~~~~
$sudo systemctl list-unit-files
~~~~

![Figura3. Salida de list-unit](/home/eduardo/Documentos/Embedded_Linux/embebidos-18-2/practicas/prac1.UsoRasp/Equipo3/imagenes/2018-02-19-221204_1366x768_scrot.png)
***Figura 3.** Demonios del sistema en ejecución listados con 'list-unit-files'.*

Como se puede observar en la figura 3, **el servicio SSH no está activado por defecto** para hacerlo, simplemente introducimos lo siguiente: 

~~~~
$ sudo systemctl status ssh
$ sudo systemctl start ssh
$ sudo systemctl enable ssh
~~~~
Lo que hacemos con *status* es comprobar si el demonio se encuentra activo o inactivo. 
Con *start* iniciamos el servicio, pero esta órden sólo lo hace para la sesión activa, al reiniciar el equipo, este vuelve a inactivarse.
Mientras que con *enable* se añade el **symlink** que permite que el servicio arranque con el sistema. 

Para conectarnos por Secure Shell, necesitamos conocer la dirección IP del *Host*, para ello preguntamos con la orden ifconfig.

~~~~
$ ifconfig
~~~~

![Figura4. SSH e Ifconfig](/home/eduardo/Documentos/Embedded_Linux/embebidos-18-2/practicas/prac1.UsoRasp/Equipo3/imagenes/2018-02-19-221408_1366x768_scrot.png)
***Figura 4.** Activando el servicio SSH y conociendo la dirección IP de nuestro dispositivo.*

En caso que no contemos con un monitor donde puedamos monitorizar nuestra Raspberry, podemos conocer la dirección IP de la mísma desde otra PC, para hacerlo sólo debemos teclear lo siguiente. 

~~~~
$ hostname -l
~~~~
Con esto, verificamos el tipo de dirección ip que tiene nuestra computadora. 

Despues, con el comando nmap preguntaremos por todas las direcciones IP que tienen activado el puerto 22 y en mi caso, utilizaré el formato que tienen las direcciones IP que asigna mi Router.  
~~~~
$ nmap -p22 192.168.1.0/24
~~~~

![Figura5. Salida comando Nmap](/home/eduardo/Documentos/Embedded_Linux/embebidos-18-2/practicas/prac1.UsoRasp/Equipo3/imagenes/nmp1)
***Figura 5.** Salida en terminal de la órden nmap*


Ahora sólo resta iniciar la conexión SSH, lo logramos con:

~~~~
$ ssh pi@192.168.1.74
~~~~
![Figura 6. Salida comando Nmap](/home/eduardo/Documentos/Embedded_Linux/embebidos-18-2/practicas/prac1.UsoRasp/Equipo3/imagenes/ssh1.png)
***Figura 6.** Conexión exitosa a SSH*

---
####Conexión vía VNC
Utilizaremos Virtual Network Computing que se basa en la arquitectura Cliente-servidor para conectarnos de manera gráfica, activaremos el servicio de la misma forma que hicimos con VNC, con la única diferencia que cambiaremos el nombre del servicio a iniciar.

~~~~
$ sudo systemctl status vncserver-x11-serviced
$ sudo systemctl start vncserver-x11-serviced
$ sudo systemctl enable vncserver-x11-serviced
~~~~

![Figura 7. Servicios VNC](/home/eduardo/Documentos/Embedded_Linux/embebidos-18-2/practicas/prac1.UsoRasp/Equipo3/imagenes/2018-02-19-222712_1366x768_scrot.png)
***Figura 7.** Servicios VNC inactivos*

Ahora, lo único que resta es iniciar el software y conectarnos al host raspberry. 

![Figura 8. Servicios VNC](/home/eduardo/Documentos/Embedded_Linux/embebidos-18-2/practicas/prac1.UsoRasp/Equipo3/imagenes/vnc1.png)
***Figura 8.** Conexión a VNC desde un PC*

También podemos conectarnos vía Android.

![Figura 9. Servicios VNC Android](/home/eduardo/Documentos/Embedded_Linux/embebidos-18-2/practicas/prac1.UsoRasp/Equipo3/imagenes/android.png)
***Figura 9.** Conexión a VNC desde un dispositivo Android*

####Conexion via FT232

En caso de no contar con un teclado, ratón o monitor, ni un equipo secundario como móvil o PC, podemos conectarnos desde un módulo UART, para hacerlo sólo debemos modificar el archivo de configuracion de la Pi, y habilitar el mini UART de la misma. Lo hacemos con:
~~~~
 $sudo nano /boot/config.txt
~~~~

Y modificamos las líneas: 
~~~~
enable_uart=1
core_freq=250
~~~~

![Figura 10. Servicios VNC Android](/home/eduardo/Documentos/Embedded_Linux/embebidos-18-2/practicas/prac1.UsoRasp/Equipo3/imagenes/2018-02-19-224258_1366x768_scrot.png)
***Figura 10.** Modificando el archivo de configuración.*

Ahora solo conectamos a la PC el módulo UART y verificamos el puerto en el que se conectó con: 

~~~~
$ ls -l /dev/ttyUSB0
~~~~ 

![Figura 11. Servicios VNC Android](/home/eduardo/Documentos/Embedded_Linux/embebidos-18-2/practicas/prac1.UsoRasp/Equipo3/imagenes/uart2.png)
***Figura 11.** Modificando el archivo de configuración.*

Para iniciar la conexión sólo se necesita ejecutar 2 órdenes. 
~~~~
$ screen /dev/ttyUSB0 115200
~~~~
Y por último, reiniciamos el equipo. 

###Referencias 
[What is a Raspberry Pi](https://opensource.com/resources/raspberry-pi)   [1]  
[Raspberry Installation](https://www.raspberrypi.org/downloads/)   [2]

