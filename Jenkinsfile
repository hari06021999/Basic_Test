pipeline {
    agent any 

    environment {
        TOOL_DIR = "${WORKSPACE}\\2W_Test\\src\\CICDTool"
    }

    stages {
        stage('Build') { 
            steps {
                bat "${TOOL_DIR}\\build.bat ${WORKSPACE}\\Debug Debug all"
            }
        }
        
    
       
    }
     post{
        always{
            emailext to: "hariprithi99@gmail.com",
            subject: "Test Email From Jenkins",
            body: "I Hope all of you getting Email's From Jenkins <br>  BUILD STATUS: ${currentBuild.currentResult}: Job ${env.JOB_NAME}\nMore Info can be found here: ${env.BUILD_URL}",
            attachLog: true
        }
    }
     
   
       
}
    
