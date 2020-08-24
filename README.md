# TP-MaquinasDeEstado---Incubadora

## Memoria Descriptiva
En este proyecto, presentamos una incubadora en la cual podremos setear la temperatura, humedad y un delta para ambas. 
Sera el sistema quien se encargara de mantener constante ambas magnitudes, las cuales seran medidas por los respectivos 
sensores. Para elevar la temperatura utilizamos un elemento calefactor o, caso contrario, un elemento refrigerante. 
Para reducir la humedad se utilizara un elemento de ventilacion.

En primera instancia, el sistema compara los datos configurados por el usuario y los que obtiene de los sensores. En base a 
esto tenemos 3 estados posibles:

   i) Calefaccion: si la temperatura leida desde el sensor, es menor a la temperatura seteada menos su delta, ingresamos a 
                   este estado donde elevaremos la temperatura hasta la seteada mas la mitad de su delta.

   ii) Refrigeracion: si la temperatura leida desde el sensor, es mayor a la temperatura seteada mas su delta. ingresamos a 
                      este estado donde reduciremos la temperatura hasta la seteada menos la mitad de su delta.

   iii) Ventilacion: si la humedad leida desde el sensor es mayor a la humedad seteada mas su delta, ingresamos a 
                     este estado donde, reduciremos la humedad hasta la seteada mas la mitad de su delta.

Se reduce o aumenta la mitad del delta ya que, si se aumentara un delta, el sistema se encontraria continuamente alternando
los estados de calefaccion y refrigeracion. Del mismo modo en el estado de ventilacion.
## Diagrama
