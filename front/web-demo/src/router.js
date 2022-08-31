import Vue from 'vue'
import Router from 'vue-router'
import Home from './views/Home.vue'
import Chart from './views/Chart.vue'
import Light from './views/Light.vue'
import Sensors from './views/Sensors.vue'
import Gate from './views/Gate.vue'

Vue.use(Router)

export default new Router({
  mode: 'history',
  base: process.env.BASE_URL,
  routes: [
    {
      path: '/',
      name: 'home',
      component: Home
    },
    {
      path: '/sensors',
      name: 'sensors',
      component: Sensors
    },
    {
      path: '/gate',
      name: 'gate',
      component: Gate
    }
  ]
})
