var termb = require('./lib/termb');

var Init = function () {
   return termb.InitTermb(1001);
}
var GetPeopleName = function () {
    var name = termb.GetPeopleName();
    console.log('姓名：'+name);
}

if(Init()==1)
{
	GetPeopleName();
}
else{
	console.log('设备初始化失败');
}


process.on('uncaughtException', function (err) {
    console.log(err);
});

process.stdin.resume();