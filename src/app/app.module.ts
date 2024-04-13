import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { RouteReuseStrategy } from '@angular/router';

import { IonicModule, IonicRouteStrategy } from '@ionic/angular';
import { initializeApp, provideFirebaseApp } from '@angular/fire/app';
import { getDatabase, provideDatabase} from '@angular/fire/database';
import { environment } from '../environments/environment'; // 

import { AppComponent } from './app.component';
import { AppRoutingModule } from './app-routing.module';

@NgModule({
  declarations: [AppComponent],
  imports: [BrowserModule,  provideFirebaseApp(() => initializeApp(environment.firebaseConfig)),
    provideDatabase(() => getDatabase()), IonicModule.forRoot(), AppRoutingModule, provideFirebaseApp(() => initializeApp({"projectId":"casadogmatica","appId":"1:887606775179:web:583a7894b1f2c9ee0ff38e","databaseURL":"https://casadogmatica-default-rtdb.firebaseio.com","storageBucket":"casadogmatica.appspot.com","apiKey":"AIzaSyBwVivZN8J0fPOLyp8pykpCn3mR6EMvT-o","authDomain":"casadogmatica.firebaseapp.com","messagingSenderId":"887606775179"}))],
  providers: [{ provide: RouteReuseStrategy, useClass: IonicRouteStrategy }],
  bootstrap: [AppComponent],
})
export class AppModule {}
