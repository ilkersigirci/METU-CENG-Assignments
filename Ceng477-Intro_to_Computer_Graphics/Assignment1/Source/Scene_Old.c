for(auto camera : pScene->cameras){
		int col = camera->imgPlane.nx;  // width = col
		int row = camera->imgPlane.ny; // heigth = row
		Image img(col, row);
		Vector3f finalColor;		
		for(int x = 0 ; x < row; x++){
			for(int y = 0 ; y < col; y++){

				Ray r = camera->getPrimaryRay(y,x);
				float t_min = FLT_MAX;
				Shape* obj = NULL;
				Color color;
				ReturnVal result, finalResult;
				for(auto o : pScene->objects){
					result = o->intersect(r);					
					if(result.isintersecting == true && result.t > 1){
						if(result.t < t_min){
							t_min = result.t;
							finalResult = result;
							obj = o;							
						}
					}
				}				
				if(obj != NULL){ // viewing ray intersected with an object 
					Material* objMaterial = pScene->materials[obj->matIndex-1];
					Vector3f ambient = (pScene->ambientLight).cwiseProduct(objMaterial->ambientRef);
					finalColor = ambient;
					img.setPixelValue(y,x,color);
					for(auto l : pScene->lights){
						// Compute Shadow
						Vector3f intersectionPoint = finalResult.intersectPoint;
						Vector3f w_i = (l->position - intersectionPoint).normalized();
						bool shadowBool = false;
						Ray shadowRay(intersectionPoint+(w_i*shadowRayEps),w_i);							
						float light_t = shadowRay.gett(l->position);
						for(auto p : pScene->objects){ // Compute Shadow
							ReturnVal shadowIntersect = p->intersect(shadowRay);
							if(shadowIntersect.isintersecting){
								if(shadowIntersect.t < light_t){
									shadowBool = true;
									break; 
								}
								else continue;
							}
						}
						if(shadowBool== true) continue;

						// Compute Diffuse				
						double w_in = w_i.dot(finalResult.surfaceNormal);
						float diffuseCos = max(0.0, w_in);
						Vector3f irradiance = (l->computeLightContribution(intersectionPoint));
						Vector3f diffuse = diffuseCos*(irradiance.cwiseProduct(objMaterial->diffuseRef));
						// Compute Specular
						Vector3f w_0 = (r.getPoint(0) - intersectionPoint).normalized();
						Vector3f h = (w_i + w_0).normalized();
						double nh = (finalResult.surfaceNormal).dot(h);
						float specularCos = max(0.0, nh);						
						Vector3f specular = pow(specularCos,objMaterial->phongExp)*((objMaterial->specularRef).cwiseProduct(irradiance));
						// Compute Final Color
						finalColor += diffuse + specular;						
						for(int i = 0; i < 3; i++){
							int temp = finalColor[i];
							temp = (temp > 255) ? 255 : temp;
							temp = (temp < 0  ) ? 0   : temp;
							finalColor[i] = temp;
						}
					}
				}				
				else{
					Vector3f bg = pScene->backgroundColor;
					for(int i = 0; i < 3; i++){
						int temp = bg[i];
						temp = (temp > 255) ? 255 : temp;
						temp = (temp < 0  ) ? 0   : temp;
						bg[i] = temp;
					}
					finalColor = bg;
				}
				color.red = finalColor[0];
				color.grn = finalColor[1];
				color.blu = finalColor[2];
				img.setPixelValue(y,x,color);
			}
			
		}
		img.saveImage(camera->imageName);
	}