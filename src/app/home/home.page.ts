import { Component } from '@angular/core';
import { Database, DatabaseReference, object, ref, set } from '@angular/fire/database';

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage {
  luzBano: boolean = false;
  luzCocina: boolean = false;
  luzDormitorio1: boolean = false;
  luzDormitorio2: boolean = false;
  luzDormitorio3: boolean = false;
  luzSala: boolean = false;

  constructor(private database: Database) {
    this.subscribeToChanges();
  }

  subscribeToChanges() {
    const banoRef: DatabaseReference = ref(this.database, "/casa/Bano");
    object(banoRef).subscribe(attributes => {
      this.luzBano = attributes.snapshot.val();
    });

    const cocinaRef: DatabaseReference = ref(this.database, "/casa/Cocina");
    object(cocinaRef).subscribe(attributes => {
      this.luzCocina = attributes.snapshot.val();
    });

    const dormitorio1Ref: DatabaseReference = ref(this.database, "/casa/Dormitorio1");
    object(dormitorio1Ref).subscribe(attributes => {
      this.luzDormitorio1 = attributes.snapshot.val();
    });

    const dormitorio2Ref: DatabaseReference = ref(this.database, "/casa/Dormitorio2");
    object(dormitorio2Ref).subscribe(attributes => {
      this.luzDormitorio2 = attributes.snapshot.val();
    });

    const dormitorio3Ref: DatabaseReference = ref(this.database, "/casa/Dormitorio3");
    object(dormitorio3Ref).subscribe(attributes => {
      this.luzDormitorio3 = attributes.snapshot.val();
    });

    const salaRef: DatabaseReference = ref(this.database, "/casa/Sala");
    object(salaRef).subscribe(attributes => {
      this.luzSala = attributes.snapshot.val();
    });
  }
  toggleLight(room: string, currentStatus: boolean) {
    const roomRef: DatabaseReference = ref(this.database, `/casa/${room}`);
    set(roomRef, !currentStatus);
  }
  
}
