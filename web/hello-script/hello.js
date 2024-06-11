function formatString(template, ...args){
    return template.replace(/{([0-9]+)}/g, function (match, index) {
    return typeof args[index] === 'undefined' ? match : args[index];
    });
}

document.addEventListener("DOMContentLoaded", function (event) {
    document.querySelector('#getName').addEventListener('submit', function (event) {
    let name = document.querySelector('#nameBox').value;
    alert(formatString('Hello {0}', name));
    event.preventDefault();
    });
});