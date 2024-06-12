document.addEventListener("DOMContentLoaded", function (event) {
    let form = document.querySelector('#getName');
    form.addEventListener('keydown', function (event) {
        if(event.keyCode === 13) 
        {
            let nameP = document.querySelector('#text');
            let input = document.querySelector('#nameBox');

            if (input.value)
                    nameP.innerHTML = `hello, ${input.value}!`;
            else
                    nameP.innerHTML = 'hello, whoever you are!';

            event.preventDefault();
            input.value = '';

            return false;
        }
    });
});


document.addEventListener("DOMContentLoaded", function (event) {
    let form = document.querySelector('#getName');
    form.addEventListener('submit', function (event) {
        let nameP = document.querySelector('#text');
        let input = document.querySelector('#nameBox');

        if (input.value)
                nameP.innerHTML = `hello, ${input.value}!`;
        else
                nameP.innerHTML = 'hello, whoever you are!';

        event.preventDefault();
        input.value = '';

        return false;
    });
});


document.addEventListener("DOMContentLoaded", function (event) {
    let input = document.querySelector('#nameBox');
    input.addEventListener('keyup', function (event) {

        if (input.value)
        {
            let nameP = document.querySelector('#text');
            nameP.innerHTML = '';

        }
    });
});