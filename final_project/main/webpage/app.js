// app.js

// Esta función se llama cuando la página se carga inicialmente
document.addEventListener("DOMContentLoaded", function () {
    // Realiza la primera actualización al cargar la página
    actualizarEstadoSensores();
    actualizarTemperatura();

    // Configura actualizaciones automáticas cada 10 segundos (puedes ajustar el intervalo según tus necesidades)
    setInterval(actualizarEstadoSensores, 500);
      setInterval(actualizarTemperatura, 5000);

});

// Función para realizar la solicitud y actualizar la interfaz
function actualizarEstadoSensores() {
    // Realiza una solicitud HTTP GET al servidor
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/estado-sensor", true);

    // Configura la función de devolución de llamada cuando la solicitud se completa
    xhr.onreadystatechange = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            // Analiza la respuesta JSON
            var jsonResponse = JSON.parse(xhr.responseText);

            // Actualiza la interfaz con los datos recibidos
            actualizarInterfaz(jsonResponse);
        }
    };

    // Envía la solicitud
    xhr.send();
}

// Función para actualizar la interfaz según el estado de los sensores
function actualizarInterfaz(estadoSensores) {
    var todosSensoresDisponibles = true;


    // Itera sobre los sensores y actualiza la interfaz
    for (var sensor in estadoSensores) {
        if (estadoSensores.hasOwnProperty(sensor)) {
            var valor = estadoSensores[sensor];
            var $elemento = document.querySelector('.' + sensor);

            // Ejemplo: Cambiar el color del fondo a rojo si el valor es 0
            if (valor == 0) {
                $elemento.style.backgroundColor = 'red';
                // Puedes realizar otras acciones según tus necesidades
            } else {
                // Restablecer el color a su estado original
                $elemento.style.backgroundColor = 'white';
            }
            if (valor !== 0) {
                todosSensoresDisponibles = false;
            }
        }
    }
    actualizarTablaSensores(estadoSensores);

    // Actualizar el estado general en algún lugar de la interfaz (por ejemplo, cambiar el color del título)
    var tituloPrincipal = document.querySelector('.titulo-principal');

    if (todosSensoresDisponibles) {
        tituloPrincipal.style.color = 'green'; // Todos los sensores disponibles, color verde
    } else {
        tituloPrincipal.style.color = 'red'; // Al menos un sensor no disponible, color rojo
    }
}

// Función para actualizar la tabla de sensores
function actualizarTablaSensores(estadoSensores) {
    // Itera sobre los sensores y actualiza las celdas de la tabla
    for (var sensor in estadoSensores) {
        if (estadoSensores.hasOwnProperty(sensor)) {
            var valor = estadoSensores[sensor];
            var $celdaSensor = document.querySelector('.celda-' + sensor);
            var $celdaTiempo = document.querySelector('.tiempo-' + sensor);

            // Verifica si se encontró la celda de la tabla
            if ($celdaSensor) {
                // Actualiza el contenido de la celda según el valor del sensor
                $celdaSensor.textContent = valor === 0 ? 'EN USO' : 'DISPONIBLE';
                if (valor == 0) {
                    iniciarCronometro($celdaTiempo);
                } else {
                    detenerCronometro($celdaTiempo);
                }
            } else {
                $celdaEstado.textContent = '---';
                detenerCronometro($celdaTiempo);
            }
        }
    }
}


// Función para iniciar un cronómetro en la celda correspondiente
// Función para iniciar un cronómetro en la celda correspondiente
function iniciarCronometro($celdaTiempo) {
    // Verifica si ya hay un cronómetro en ejecución
    if ($celdaTiempo.dataset.intervalId) {
        return;
    }

    var segundos = 0;

    // Actualiza el contenido de la celda cada segundo
    var cronometroInterval = setInterval(function () {
        segundos++;
        $celdaTiempo.textContent = formatearTiempo(segundos);
    }, 1000);

    // Almacena el identificador del intervalo en la celda (para detenerlo más tarde si es necesario)
    $celdaTiempo.dataset.intervalId = cronometroInterval;
}

// Función para detener un cronómetro en la celda correspondiente
function detenerCronometro($celdaTiempo) {
    // Detiene el intervalo solo si hay un cronómetro en ejecución
    if ($celdaTiempo.dataset.intervalId) {
        clearInterval($celdaTiempo.dataset.intervalId);
        delete $celdaTiempo.dataset.intervalId;
    }

    // Reinicia el contenido de la celda solo si no está vacía
    if ($celdaTiempo.textContent !== '---') {
        $celdaTiempo.textContent = '---';
    }
}



// Función para formatear el tiempo en formato HH:MM:SS
function formatearTiempo(segundos) {
    var horas = Math.floor(segundos / 3600);
    var minutos = Math.floor((segundos % 3600) / 60);
    var segundosRestantes = segundos % 60;

    return (
        padZero(horas) + ':' + padZero(minutos) + ':' + padZero(segundosRestantes)
    );
}

// Función para asegurarse de que los números tengan dos dígitos (agrega cero a la izquierda si es necesario)
function padZero(numero) {
    return numero < 10 ? '0' + numero : numero;
}

function actualizarTemperatura() {
    // Realizar una solicitud HTTP para obtener la temperatura del servidor
    $.get("/temperatura", function (data) {
        // Actualizar el contenido de #temperatura-valor con el nuevo valor de temperatura
        $("#temperatura-valor").text(data.temperature.toFixed(2) + " °C");
    });
}

function bloquearSistema() {
    // Realiza una solicitud POST al servidor para bloquear el sistema
    fetch('/bloquear-sistema', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({}),
    })
      .then(response => response.text())
      .then(data => {
        // Muestra una ventana emergente con la respuesta del servidor
        window.alert('Respuesta del servidor: ' + data);
      })
      .catch(error => {
        console.error('Error al realizar la solicitud:', error);
      });
  }