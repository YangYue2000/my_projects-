package schedule;

import java.util.Vector;
import java.util.jar.Attributes.Name;

public class Class {
	public String name;
	public Vector<session> sessions = new Vector<session>();
	public Vector<Class> sub_classes = new Vector<Class>();
//	if it's a math class, certain discussion sessions can only be registered
//	with a specific lecture
}
