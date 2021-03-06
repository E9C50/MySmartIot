// index.js
// 获取应用实例
const app = getApp()

Page({
  data: {
    userInfo: {},
    hasUserInfo: false,
    canIUse: wx.canIUse('button.open-type.getUserInfo'),
    canIUseGetUserProfile: false,
    canIUseOpenData: wx.canIUse('open-data.type.userAvatarUrl') && wx.canIUse('open-data.type.userNickName'), // 如需尝试获取用户信息可改为false
    switchLedLight: false,
    switchBedroomLight: false,
    hiddenSmartWifi: true
  }, 
  changeSwitchLedLight(event) {
    let payload = event.detail.value ? 'OPEN_LED' : 'CLOSE_LED';
    wx.request({
      url: 'https://api.fuxin516.com/iotServer/publishMessage',
      data: {
        'deviceName': 'NodeMCU-8266',
        'payload': payload
      },
      header: {
        'content-type': 'application/json'
      },
      success(res) {
        if (res.statusCode == 200) {
          wx.showToast({
            title: '操作成功',
            icon: "success",
            duration: 1000
          })
        } else {
          wx.showToast({
            title: '操作失败' + res.statusCode,
            icon: "error",
            duration: 1000
          })
        }
      }
    })
  },
  changeSwitchBedroomLight(event) {
    let payload = event.detail.value ? '170' : '10';
    wx.request({
      url: 'https://api.fuxin516.com/iotServer/publishMessage',
      data: {
        'deviceName': 'NodeMCU-8266',
        'payload': payload
      },
      header: {
        'content-type': 'application/json'
      },
      success(res) {
        if (res.statusCode == 200) {
          wx.showToast({
            title: '操作成功',
            icon: "success",
            duration: 1000
          })
        } else {
          wx.showToast({
            title: '操作失败' + res.statusCode,
            icon: "error",
            duration: 1000
          })
        }
      }
    })
  },
  tapSmartWifi() {
    this.setData({
      hiddenSmartWifi: false
    })
  },
  cancelSmartWifi: function () {
    this.setData({
      hiddenSmartWifi: true
    });
  },
  confirmSmartWifi: function () {
    this.setData({
      hiddenSmartWifi: true
    })
    wx.showToast({
      title: 'TMD...代码又被崔经理那个狗产品删掉了...',
      icon: 'none'
    })
  },
  onLoad() {
    if (wx.getUserProfile) {
      this.setData({
        canIUseGetUserProfile: true
      })
    }
  },
  getUserProfile(e) {
    // 推荐使用wx.getUserProfile获取用户信息，开发者每次通过该接口获取用户个人信息均需用户确认，开发者妥善保管用户快速填写的头像昵称，避免重复弹窗
    wx.getUserProfile({
      desc: '展示用户信息', // 声明获取用户个人信息后的用途，后续会展示在弹窗中，请谨慎填写
      success: (res) => {
        console.log(res)
        this.setData({
          userInfo: res.userInfo,
          hasUserInfo: true
        })
      }
    })
  },
  getUserInfo(e) {
    // 不推荐使用getUserInfo获取用户信息，预计自2021年4月13日起，getUserInfo将不再弹出弹窗，并直接返回匿名的用户个人信息
    console.log(e)
    this.setData({
      userInfo: e.detail.userInfo,
      hasUserInfo: true
    })
  }
})