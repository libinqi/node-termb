var termb = require('./lib/termb');

var Init = function () {
   return termb.InitTermb(1001);
}
var GetPeopleName = function () {
    var name = termb.GetPeopleName();
    console.log('������'+name);
}

if(Init()==1)
{
	GetPeopleName();
}
else{
	console.log('�豸��ʼ��ʧ��');
}


process.on('uncaughtException', function (err) {
    console.log(err);
});

process.stdin.resume();