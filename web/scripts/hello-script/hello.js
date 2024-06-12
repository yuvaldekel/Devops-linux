document.addEventListener("DOMContentLoaded", function (event) {
    document.querySelector('#getName').addEventListener('submit', function (event) {
        let name = document.querySelector('#nameBox').value;
        alert(`Hello ${name}`);
        event.preventDefault();
    });
});