<template>
  <v-app id="inspire">
    <v-navigation-drawer v-model="drawer" fixed app clipped>
      <v-list dense>
        <v-list-tile to="/">
          <v-list-tile-action>
            <v-icon>home</v-icon>
          </v-list-tile-action>
          <v-list-tile-content>
            <v-list-tile-title>Home</v-list-tile-title>
          </v-list-tile-content>
        </v-list-tile>
        <v-list-tile to="/sensors">
          <v-list-tile-action>
            <v-icon>sensors</v-icon>
          </v-list-tile-action>
          <v-list-tile-content>
            <v-list-tile-title>Sensors</v-list-tile-title>
          </v-list-tile-content>
        </v-list-tile>
        <v-list-tile to="/gate">
          <v-list-tile-action>
            <v-icon>door_sliding</v-icon>
          </v-list-tile-action>
          <v-list-tile-content>
            <v-list-tile-title>Gate</v-list-tile-title>
          </v-list-tile-content>
        </v-list-tile>
      </v-list>
    </v-navigation-drawer>
    <v-toolbar color="blue" dark fixed app clipped-left>
      <v-toolbar-side-icon @click.stop="drawer = !drawer"></v-toolbar-side-icon>
      <v-toolbar-title>IoT Manager</v-toolbar-title>
    </v-toolbar>
    <v-content>
      <v-container fluid fill-height>
        <router-view></router-view>
      </v-container>
    </v-content>
    <v-footer color="blue" app fixed>
      <span class="white--text">&ensp;&copy; Lok'tar ogar!</span>
    </v-footer>
  </v-app>
</template>

<script>
export default {
  name: 'App',
  data () {
    return {
      drawer: null
    }
  }
}
</script>
