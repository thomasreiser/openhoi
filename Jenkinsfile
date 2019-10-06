pipeline {
    agent any
    
    options {
		buildDiscarder(logRotator(numToKeepStr: '10'))
	}
    
    parameters {
		booleanParam name: 'CREATE_APPIMAGE', defaultValue: false, description: 'Build AppImage?'
	}
    
    stages {
        stage('Prepare') {
            steps {
                sh "chmod +x fetch-deps"
                sh "./fetch-deps"
            }
        }
        stage('Build') {
            steps {
                cmakeBuild
                    buildType: 'RelWithDebInfo',
                    cleanBuild: true,
                    installation: 'InSearchPath',
                    steps: [
                        [withCmake: true]
                    ]
            }
        }
        stage('Test') {
            steps {
                ctest 'InSearchPath'
            }
        }
    }
    
    post {
        always {
            deleteDir()
        }
    }
}