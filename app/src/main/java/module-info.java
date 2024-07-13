module cyran.volume_mixer.volume_mixer_app {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;

    opens cyran.volume_mixer.volume_mixer_app to javafx.fxml;
    exports cyran.volume_mixer.volume_mixer_app;
}