# Vue.js

MVVM：Model-View-ViewModel

ViewModel双向绑定View与Model

使用模板编程，更改数据即时显示不用刷新，不操作DOM

在底层的实现上，Vue 将模板编译成虚拟 DOM 渲染函数。结合响应系统，Vue 能够智能地计算出最少需要重新渲染多少组件，并把 DOM 操作次数减到最少

```html
<div id="app">
    {{message}}
</div>
<script>
    var vm = new Vue({
        el:"#app",
        data:{
            message:"hello"
        }
    })
</script>
```



# 属性

```javascript
var vm = new Vue({
  el: '#demo',
  data: {
    firstName: 'Foo',
    lastName: 'Bar',
    fullName: 'Foo Bar'
  },
  
})
```



**方法属性**

每当触发重新渲染时，调用方法将总会执行函数

```javascript
methods: {
  reversedMessage: function () {
    return this.message.split('').reverse().join('')
  }
}
```

**计算属性**

计算属性是基于它们的响应式依赖进行缓存的

```javascript
computed: {
  now: function () {
    return Date.now()
  },
  fullName: function () {
    return this.firstName + ' ' + this.lastName
  }
}
```

**侦听属性**

```javascript
watch: {
  // 如果 `firstName` 发生改变，这个函数就会运行
  firstName: function (val) {
    this.fullName = val + ' ' + this.lastName
  },
  // 如果 `lastName` 发生改变，这个函数就会运行
  lastName: function (val) {
    this.fullName = this.firstName + ' ' + val
  }
}
```



# 指令

```html
<!-- v-bind绑定到属性 -->
<span v-bind:title="message"/>
<span :title="message"/>

<!-- v-if v-else -->
<p v-if="seen">现在你看到我了</p>
<p v-else>现在你看不到我了</p>
<div v-else-if="type === 'show'">

<!-- v-for -->
<li v-for="(item, index) in items">
  {{ parentMessage }} - {{ index }} - {{ item.message }}
</li>
<div v-for="(value, name, index) in object">
  {{ index }}. {{ name }}: {{ value }}
</div>
    
<!-- v-show根据条件展示元素,只是简单地切换元素的 CSS property -->    
<h1 v-show="ok">Hello!</h1>

<!-- v-on事件监听器 -->
<button v-on:click="reverseMessage">反转消息</button>
<button @click="reverseMessage">反转消息</button>

<!-- v-once一次性地插值 -->
<span v-once>这个将不会改变: {{ msg }}</span>

<!-- v-html插入html -->
<span v-html="rawHtml"></span>
```

