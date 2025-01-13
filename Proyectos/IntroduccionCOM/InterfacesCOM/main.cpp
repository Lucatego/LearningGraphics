//Una interfaz para los dibujos
class IDrawable{
    public:
        virtual void Draw() = 0;
};
//Una interfaz para los objetos serializables
class ISerializable{
    public:
        virtual void Load(const char * filename) = 0;
        virtual void Save(const char * filename) = 0;
};

//Una clase que hereda de la interfaz
class Figura : public IDrawable{
    private:
        // ...
    public:
        virtual void Draw(){

        };
};

//Una clase que hereda de 2 interfaces
class Bitmap : public IDrawable, public ISerializable{
    private:
        // ...
    public:
        virtual void Draw(){
            // ...
        }

        virtual void Load(const char * filename){
            // ...
        }

        virtual void Save(const char * filename){
            // ...
        }
};

//Programa sin funcionalidad.
int main(void){
    // Ejemplos de uso:
    IDrawable * draw = new Figura();
    IDrawable * writing = new Bitmap();
    //Uso de interfaces:
    draw->Draw();
    writing->Draw();
    //Fin
    return 0;
}