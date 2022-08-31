import Vue from 'vue'
import Vuex from 'vuex'
import axios from 'axios'

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    temperature: localStorage.temperature ? localStorage.temperature : [0, 0, 0, 0, 0, 0, 0, 0],
    humidity: localStorage.humidity ? localStorage.humidity : [0, 0, 0, 0, 0, 0, 0, 0]
  },
  mutations: {
    update_sensors(state, data) {
      state.temperature.push(data.temperature);
      state.temperature.shift();
      state.humidity.push(data.humidity);
      state.humidity.shift();
    }
  },
  actions: {
    update_sensors({ commit }) {
      axios.get("/api/v1/sensor/data")
        .then(data => {
          commit("update_sensors", data.data);
        })
        .catch(error => {
          console.log(error);
        });
    }
  }
})
