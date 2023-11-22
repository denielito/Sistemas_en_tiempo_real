function toggleLED(led) {
    fetch('/toggle_led?color=' + led, {
        method: 'POST',
    })
    .then(response => response.json())
    .then(data => {
        // Puedes manejar la respuesta si es necesario
        console.log(data);
    })
    .catch(error => {
        console.error('Error:', error);
    });
}
