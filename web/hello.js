function formatString(template, ...args){
    return template.replace(/{([0-9]+)}/g, function (match, index) {
      return typeof args[index] === 'undefined' ? match : args[index];
    });
}

for (let i = 0; i < 10; ++i){
    if ( i % 2 == 0)
        console.log(formatString('Hello World, i is {0}', i));
    else
    console.log('Hello World');

}