/**
 * Created by libinqi on 2015/6/18.
 */
var addon = require('../build/Release/termb.node');
var termb = new addon.Termb();

/**
 * 读取卡ID
 *
 * @param nCom // int类型,设备端口号
 * @return 返回值为int类型,返回值为1成功,否则失败
 */
exports.InitTermb = function (nCom) {
    try {
        var result = termb.InitComm(nCom);
        if(result!=1)
        {
            return 0;
        }
        result = termb.Authenticate();
        if (result != 1) {
            return 0;
        }
        result = termb.Read_Content(1);
        if (result != 1) {
            return 0;
        }
        return result;
    }
    catch (ex) {
        console.log(ex);
    }
};

/**
 * 关闭读取卡
 *
 * @return 返回值为int类型,返回值为1成功,否则失败
 */
exports.CloseTermb = function () {
    try {
        var result = termb.InitComm();
        return result;
    }
    catch (ex) {
        console.log(ex);
    }
};

/**
 * 读取姓名
 *
 * @return 返回值为字符串类型,返回值不为0成功,否则失败
 */
exports.GetPeopleName = function () {
    try {
        var result = termb.GetPeopleName();
        return result;
    }
    catch (ex) {
        console.log(ex);
    }
};

/**
 * 读取性别
 *
 * @return 返回值为字符串类型,返回值不为0成功,否则失败
 */
exports.GetPeopleSex = function () {
    try {
        var result = termb.GetPeopleSex();
        return result;
    }
    catch (ex) {
        console.log(ex);
    }
};

/**
 * 读取签发机关
 *
 * @return 返回值为字符串类型,返回值不为0成功,否则失败
 */
exports.GetPeopleNation = function () {
    try {
        var result = termb.GetPeopleNation();
        return result;
    }
    catch (ex) {
        console.log(ex);
    }
};

/**
 * 读取出生日期
 *
 * @return 返回值为字符串类型,返回值不为0成功,否则失败
 */
exports.GetPeopleBirthday = function () {
    try {
        var result = termb.GetPeopleBirthday();
        return result;
    }
    catch (ex) {
        console.log(ex);
    }
};

/**
 * 读取地址
 *
 * @return 返回值为字符串类型,返回值不为0成功,否则失败
 */
exports.GetPeopleAddress = function () {
    try {
        var result = termb.GetPeopleAddress();
        return result;
    }
    catch (ex) {
        console.log(ex);
    }
};

/**
 * 读取身份证号码
 *
 * @return 返回值为字符串类型,返回值不为0成功,否则失败
 */
exports.GetPeopleIDCode = function () {
    try {
        var result = termb.GetPeopleIDCode();
        return result;
    }
    catch (ex) {
        console.log(ex);
    }
};

/**
 * 读取有效起始日期
 *
 * @return 返回值为字符串类型,返回值不为0成功,否则失败
 */
exports.GetStartDate = function () {
    try {
        var result = termb.GetStartDate();
        return result;
    }
    catch (ex) {
        console.log(ex);
    }
};

/**
 * 读取有效截止日期
 *
 * @return 返回值为字符串类型,返回值不为0成功,否则失败
 */
exports.GetEndDate = function () {
    try {
        var result = termb.GetEndDate();
        return result;
    }
    catch (ex) {
        console.log(ex);
    }
};