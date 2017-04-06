//AARON COLSTON AVELLA HILES - 48337779J

//SIN TOCAR
void Pathfinding::astar() {
	int pos = listM.front();

	if(first == 0){
		posPrev = getPos();
	}

	if(first == 0 && pos == 3 && m->getC(((int)getPS()->getPos().X()/2), ((int)getPS()->getPos().Z / 2) + 1) != 0) {
		list.erase(listM.begin());
		list.insert(listM.begin(), 4);
		list.insert(listM.begin() + 1, 2);
		pos = listM.front();
	}else if (first == 0 && pos == 3 && m->getC(((int)getPS()->getPos().X()/2), ((int)getPS()->getPos().Z / 2)+1) != 0) {
		list.erase(listM.begin());
		list.insert(listM.begin(), 4);
		list.insert(listM.begin() + 1, 2);
		pos = listM.front();
	}
}


///////////////////////////////

//MEJORADO??
void Pathfinding::astar() {
	int pos = listM.front();
	int a,b;
	int datosX = (int)getPS()->getPos().X() / 2;
	int datosZ = (int)getPS()->getPos().Z() / 2;

	if(first == 0 && pos == 3){
		if(m->getC(datosX, datosZ + 1) != 0){
			a = 4;
			b = 2;
		}else if(m->getC(datosX-1, datosZ) != 0){
			a = 2;
			b = 4;
		}
	}

	ist.erase(listM.begin());
	list.insert(listM.begin(), a);
	list.insert(listM.begin() + 1, b);
	pos = listM.front();
}


///////////////////////////////

//MEJORADO
void mods(int v1, int v2){
	listM.pop_front();
	listM.push_front(v1);
	listM.push_front(v2);
	pos = listM.front();
}

void Pathfinding::astar() {
	//PS * p 	= getPS();    //---- esto es una positiblidad si pones debajo -------  TPos pt = p->getPos();
	TPos pt = getPS()->getPos();
	int x = (int)pt.X() / 2;
	int z = (int)pt.Z() / 2;

	//int x = (int)getPS()->getPos().X() / 2;
	//int z = (int)getPS()->getPos().Z() / 2;

	int pos = listM.front();
	if(first == 0 && pos == 3){
		if     (m->getC(x, z+1))		mods(4,2);
		else if(m->getC(x-1, z))		mods(2,4);	
	}
}
